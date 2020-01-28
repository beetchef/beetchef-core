#include "jack_audio_provider.hpp"

#include "jack_audio_interface.hpp"
#include "jack_client_wrapper.hpp"

#include <memory>

Jack_audio_provider::Jack_audio_provider(std::unique_ptr<Jack_client_wrapper> client)
    : _client{std::move(client)}
    , _audio_interface{std::make_unique<Jack_audio_interface>(_client.get())}
{
}

Audio_interface* Jack_audio_provider::get_audio_interface()
{
    return _audio_interface.get();
}
