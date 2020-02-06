#ifndef AUDIO_BASE_HPP
#define AUDIO_BASE_HPP

#include "audio_interface.hpp"

#include <memory>

class Audio_base {
    public:
        template<typename T>
        Audio_base(T impl_provider)
            : _impl_provider{std::make_unique<Impl_provider_model<T>>(std::move(impl_provider))}
            , _audio_interface(get_impl_provider<T>().create_audio_interface())
        { }

        Audio_interface* get_audio_interface();

        template<typename T>
        void reset_impl_provider(T impl_provider)
        {
            _impl_provider = std::make_unique<Impl_provider_model<T>>(std::move(impl_provider));
            _audio_interface.reset_impl(get_impl_provider<T>().create_audio_interface());
        }

    private:

        template<typename T>
        auto& get_impl_provider()
        {
            return static_cast<Impl_provider_model<T>&>(*_impl_provider)._self;
        }

        struct Impl_provider_concept {
            virtual ~Impl_provider_concept() = default;
        };

        template<typename T>
        struct Impl_provider_model final : Impl_provider_concept {
            Impl_provider_model(T self) : _self(std::move(self))
            { }
            T _self;
        };

        std::unique_ptr<Impl_provider_concept> _impl_provider;
        Audio_interface _audio_interface;
};

#endif // AUDIO_BASE_HPP
