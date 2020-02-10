#ifndef BEETCHEF_AUDIO_INTERFACE_HPP
#define BEETCHEF_AUDIO_INTERFACE_HPP

#include "audio_types.hpp"
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
            _pimpl->register_process_callback(Callback_function{std::move(callback)});
        }

    private:

        struct Impl_concept {
            virtual ~Impl_concept() = default;
            virtual sample_t* get_in_buf(int chan_idx, nframes_t nframes) /*const ? */ = 0;
            virtual sample_t* get_out_buf(int chan_idx, nframes_t nframes) = 0;
            virtual void register_process_callback(Callback_function callback) = 0;
        };

        template<typename T>
        struct Impl_model final : public Impl_concept {
            explicit Impl_model(T self) : _self{std::move(self)}
            { }

            sample_t* get_in_buf(int chan_idx, nframes_t nframes) /*const ? */ override
            {
                return _self.get_in_buf(chan_idx, nframes);
            }

            sample_t* get_out_buf(int chan_idx, nframes_t nframes) /*const ? */ override
            {
                return _self.get_out_buf(chan_idx, nframes);
            }

            void register_process_callback(Callback_function callback) override
            {
                _self.register_process_callback(std::move(callback));
            }

            T _self;
        };

        std::unique_ptr<Impl_concept> _pimpl;
};

#endif // BEETCHEF_AUDIO_INTERFACE_HPP
