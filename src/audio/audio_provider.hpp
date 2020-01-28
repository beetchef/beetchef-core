#ifndef AUDIO_FACTORY_HPP
#define AUDIO_FACTORY_HPP

#include "audio_interface.hpp"

class Audio_provider {
    public:
        virtual ~Audio_provider() {}
        virtual Audio_interface* get_audio_interface() = 0;
};

#endif // AUDIO_FACTORY_HPP
