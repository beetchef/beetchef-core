#include "audio_base.hpp"
#include "audio_interface.hpp"

Audio_interface* Audio_base::get_audio_interface()
{
    return &_audio_interface;
}
