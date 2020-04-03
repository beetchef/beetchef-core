#include "audio/audio_base.hpp"
#include "audio/audio_interface.hpp"

Audio_interface* Audio_base::get_audio_interface()
{
    return &_audio_interface;
}
