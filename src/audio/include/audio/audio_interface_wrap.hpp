#ifndef BEETCHEF_AUDIO_INTERFACE_WRAP_HPP
#define BEETCHEF_AUDIO_INTERFACE_WRAP_HPP

#include "callback_function.hpp"
#include "types.hpp"

#include <memory>
#include <optional>

class Audio_interface_wrap {
    public:
        template<typename T>
        explicit Audio_interface_wrap(T audio_interface)
            : _audio_interface{std::make_unique<Audio_interface_model<T>>(std::move(audio_interface))}
        { }

        template<typename T>
        void reset_audio_interface(T audio_interface)
        {
            _audio_interface = std::make_unique<Audio_interface_model<T>>(std::move(audio_interface));
        }

        template<typename T>
        bool register_process_callback(T callable)
        {
            _callback.emplace(callable);
            
            bool res = _audio_interface->set_process_callback(&_callback.value());

            if (!res)
            {
               _callback.reset(); 
            }

            return res;
        }

        bool unregister_process_callback();

        bool start_processing();
        bool stop_processing();

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
            virtual bool set_process_callback(Callback_function* callback) = 0;
            virtual bool unset_process_callback() = 0;
            virtual bool start_processing() = 0;
            virtual bool stop_processing() = 0;
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

            bool set_process_callback(Callback_function* callback) override
            {
                return _self.set_process_callback(callback);
            }

            bool unset_process_callback() override
            {
                return _self.unset_process_callback();
            }

            bool start_processing() override
            {
                return _self.start_processing();
            }

            bool stop_processing() override
            {
                return _self.stop_processing();
            }

            T _self;
        };

        std::unique_ptr<Audio_interface_concept> _audio_interface;
        std::optional<Callback_function> _callback;
};

#endif // BEETCHEF_AUDIO_INTERFACE_WRAP_HPP