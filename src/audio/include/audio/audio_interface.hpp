#ifndef BEETCHEF_AUDIO_INTERFACE_HPP
#define BEETCHEF_AUDIO_INTERFACE_HPP

#include "types.hpp"
#include "callback_function.hpp"

#include <memory>

class Audio_interface {
    public:

        template<typename T>
        explicit Audio_interface(T impl)
            : _pimpl{std::make_unique<Impl_model<T>>(std::move(impl))}
        { }

        template<typename T>
        void reset_impl(T impl)
        {
            _pimpl = std::make_unique<Impl_model<T>>(std::move(impl));
        }

        template<typename T>
        void register_process_callback(T callback)
        {
            _callback = std::make_unique<Callback_function>(callback);
            _pimpl->set_process_callback(_callback.get());
        }

        nframes_t get_sample_rate() const;

        int get_in_chan_count() const;
        int get_out_chan_count() const;

        sample_t* get_in_buf(int chan_idx, nframes_t nframes_t) const;
        sample_t* get_out_buf(int chan_idx, nframes_t nframes_t) const;

    private:

        struct Impl_concept {
            virtual ~Impl_concept() = default;
            virtual nframes_t get_sample_rate() const = 0;
            virtual int get_in_chan_count() const = 0;
            virtual int get_out_chan_count() const = 0;
            virtual sample_t* get_in_buf(int chan_idx, nframes_t nframes) const = 0;
            virtual sample_t* get_out_buf(int chan_idx, nframes_t nframes) const = 0;
            virtual void set_process_callback(Callback_function* callback) = 0;
        };

        template<typename T>
        struct Impl_model final : public Impl_concept {
            explicit Impl_model(T self) : _self{std::move(self)}
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

            T _self;
        };

        std::unique_ptr<Impl_concept> _pimpl;
        std::unique_ptr<Callback_function> _callback;
};

#endif // BEETCHEF_AUDIO_INTERFACE_HPP
