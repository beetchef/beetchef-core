#ifndef JACK_AUDIO_FACTORY_HPP
#define JACK_AUDIO_FACTORY_HPP

#include "audio/audio_provider.hpp"
#include "jack_audio_interface.hpp"
#include "jack_client_wrapper.hpp"

#include <memory>

class Jack_audio_provider : public Audio_provider {
    public:
        Jack_audio_provider(std::unique_ptr<Jack_client_wrapper>);
        Audio_interface* get_audio_interface() override;
    private:
        std::unique_ptr<Jack_client_wrapper> _client;
        std::unique_ptr<Jack_audio_interface> _audio_interface;
};

#endif // JACK_AUDIO_FACTORY_HPP
