#ifndef BEETCHEF_AUDIO_INTERFACE_HPP
#define BEETCHEF_AUDIO_INTERFACE_HPP

#include "audio_types.hpp"

#include <memory>

class Audio_interface {
    public:

        template<typename T>
        Audio_interface(T impl)
            : _pimpl{std::make_unique<Impl_model<T>>(std::move(impl))}
        { }

        template<typename T>
        void reset_impl(T impl)
        {
            _pimpl = std::make_unique<Impl_model<T>>(std::move(impl));
        }

        sample_t* get_in_buf(int chan_idx, nframes_t nframes_t) const
        {
            return _pimpl->get_in_buf(chan_idx, nframes_t);
        }

        sample_t* get_out_buf(int chan_idx, nframes_t nframes_t) const
        {
            return _pimpl->get_out_buf(chan_idx, nframes_t);
        }

        void set_process_callback(/* TBD */)
        {
            _pimpl->set_process_callback(/* TBD */);
        }

    private:

        struct Impl_concept {
            virtual ~Impl_concept() = default;
            virtual sample_t* get_in_buf(int chan_idx, nframes_t nframes) /*const ? */ = 0;
            virtual sample_t* get_out_buf(int chan_idx, nframes_t nframes) = 0;
            virtual void set_process_callback(/* TBD */) = 0;
        };

        template<typename T>
        struct Impl_model final : public Impl_concept {
            Impl_model(T self) : _self{std::move(self)}
            { }

            sample_t* get_in_buf(int chan_idx, nframes_t nframes) /*const ? */ override
            {
                return _self.get_in_buf(chan_idx, nframes);
            }

            sample_t* get_out_buf(int chan_idx, nframes_t nframes) /*const ? */ override
            {
                return _self.get_out_buf(chan_idx, nframes);
            }

            void set_process_callback(/* TBD */) override
            {
                _self.set_process_callback(/* TBD */);
            }

            T _self;
        };

        std::unique_ptr<Impl_concept> _pimpl;
};

#endif // BEETCHEF_AUDIO_INTERFACE_HPP
