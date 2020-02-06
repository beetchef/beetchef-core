#ifndef JACK_AUDIO_FACTORY_HPP
#define JACK_AUDIO_FACTORY_HPP

#include "jack_audio_interface.hpp"
#include "jack_client_wrapper.hpp"

#include <memory>

class Jack_impl_provider {
    public:
        Jack_impl_provider(Jack_client_wrapper);
        Jack_impl_provider(const Jack_impl_provider&) = delete;
        Jack_impl_provider(Jack_impl_provider&&) = default;
        Jack_impl_provider& operator=(const Jack_impl_provider) = delete;
        Jack_impl_provider& operator=(Jack_impl_provider&&) = default;
        ~Jack_impl_provider() = default;
        Jack_audio_interface create_audio_interface();
    private:
        Jack_client_wrapper _jack_client;
};

#endif // JACK_AUDIO_FACTORY_HPP
