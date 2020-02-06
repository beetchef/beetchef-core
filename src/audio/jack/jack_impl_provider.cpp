#include "jack_audio_interface.hpp"
#include "jack_client_wrapper.hpp"
#include "jack_impl_provider.hpp"

#include <memory>

Jack_impl_provider::Jack_impl_provider(Jack_client_wrapper jack_client)
    : _jack_client(std::move(jack_client))
{
}

Jack_audio_interface Jack_impl_provider::create_audio_interface()
{
    return Jack_audio_interface(&_jack_client);
}
