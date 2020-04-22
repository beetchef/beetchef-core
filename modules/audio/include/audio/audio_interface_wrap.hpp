/*
 *  Beetchef - real time audio sequencer
 *  Copyright (C) 2020 Anton Šefčík
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BEETCHEF_AUDIO_INTERFACE_WRAP_HPP
#define BEETCHEF_AUDIO_INTERFACE_WRAP_HPP

#include "callback_function.hpp"
#include "types.hpp"

#include <memory>

namespace Audio
{
    class Audio_interface_wrap {
        public:
            template<typename T>
            explicit Audio_interface_wrap(T audio_interface)
                : _audio_interface{std::make_unique<Audio_interface_model<T>>(std::move(audio_interface))}
                , _callback{dummy_callback}
            {
                _audio_interface->set_process_callback(&_callback);
            }

            // disable move/copy operations because _callback member is being referenced by _audio_intertface member
            // meaning that the address of _callback is not supposed to change
            Audio_interface_wrap(const Audio_interface_wrap&) = delete;
            Audio_interface_wrap(Audio_interface_wrap&&) = delete;
            Audio_interface_wrap& operator=(const Audio_interface_wrap&) = delete;
            Audio_interface_wrap& operator=(Audio_interface_wrap&&) = delete;

            template<typename T>
            void reset_audio_interface(T audio_interface)
            {
                _audio_interface = std::make_unique<Audio_interface_model<T>>(std::move(audio_interface));
                _audio_interface->set_process_callback(&_callback);
            }

            template<typename T>
            void register_process_callback(T callable)
            {
                _callback = Callback_function{callable};
            }

            void unregister_process_callback();

            void start_processing();
            void stop_processing();

            nframes_t get_sample_rate() const;

            int get_in_chan_count() const;
            int get_out_chan_count() const;

            sample_t* get_in_buf(int chan_idx, nframes_t nframes_t) const;
            sample_t* get_out_buf(int chan_idx, nframes_t nframes_t) const;

        private:
            struct Audio_interface_concept {
                virtual ~Audio_interface_concept() = default;
                virtual nframes_t get_sample_rate() const = 0;
                virtual int get_in_chan_count() const = 0;
                virtual int get_out_chan_count() const = 0;
                virtual sample_t* get_in_buf(int chan_idx, nframes_t nframes) const = 0;
                virtual sample_t* get_out_buf(int chan_idx, nframes_t nframes) const = 0;
                virtual void set_process_callback(Callback_function* callback) = 0;
                virtual void unset_process_callback() = 0;
                virtual void start_processing() = 0;
                virtual void stop_processing() = 0;
            };

            template<typename T>
            struct Audio_interface_model final : public Audio_interface_concept {
                explicit Audio_interface_model(T self) : _self{std::move(self)}
                { }

                nframes_t get_sample_rate() const
                {
                    return _self.get_sample_rate();
                }

                int get_in_chan_count() const
                {
                    return _self.get_in_chan_count();
                }

                int get_out_chan_count() const
                {
                    return _self.get_out_chan_count();
                }

                sample_t* get_in_buf(int chan_idx, nframes_t nframes) const override
                {
                    return _self.get_in_buf(chan_idx, nframes);
                }

                sample_t* get_out_buf(int chan_idx, nframes_t nframes) const override
                {
                    return _self.get_out_buf(chan_idx, nframes);
                }

                void set_process_callback(Callback_function* callback) override
                {
                    _self.set_process_callback(callback);
                }

                void unset_process_callback() override
                {
                    _self.unset_process_callback();
                }

                void start_processing() override
                {
                    return _self.start_processing();
                }

                void stop_processing() override
                {
                    return _self.stop_processing();
                }

                T _self;
            };

            std::unique_ptr<Audio_interface_concept> _audio_interface;
            Callback_function _callback;
    };

}; // namespace Audio

#endif // BEETCHEF_AUDIO_INTERFACE_WRAP_HPP