#ifndef BEETCHEF_JACK_IMPL_PROVIDER_HPP
#define BEETCHEF_JACK_IMPL_PROVIDER_HPP

#include "jack_audio_interface.hpp"
#include "jack_client.hpp"

#include <memory>

class Jack_impl_provider {
    public:
        explicit Jack_impl_provider(Jack_client);
        Jack_impl_provider(const Jack_impl_provider&) = delete;
        Jack_impl_provider(Jack_impl_provider&&) = default;
        Jack_impl_provider& operator=(const Jack_impl_provider) = delete;
        Jack_impl_provider& operator=(Jack_impl_provider&&) = default;
        ~Jack_impl_provider() = default;
        Jack_audio_interface create_audio_interface();
    private:
        Jack_client _jack_client;
};

#endif // BEETCHEF_JACK_IMPL_PROVIDER_HPP
