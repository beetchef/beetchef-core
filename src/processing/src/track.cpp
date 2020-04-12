#include <audio/audio_interface_wrap.hpp>
#include <audio/types.hpp>

#include <processing/track.hpp>
#include <processing/types.hpp>

#include <algorithm>
#include <cstring>
#include <string>

using Processing::Track;

Track::Track(Audio::Audio_interface_wrap* const audio_interface, const std::vector<int> in_chans, const std::string name)
    : _audio_interface{audio_interface}
    , _in_chans{in_chans}
    , _name{name}
{
}

void
Track::produce_to(const int chan_idx, const Process_frame& process_frame, Audio::sample_t* out_buf)
{
    Audio::sample_t* in_buf = _audio_interface->get_in_buf(_in_chans[chan_idx], process_frame.nframes);

    std::copy(in_buf, in_buf + process_frame.nframes, out_buf);

    //std::memcpy(out_buf, _audio_interface->get_in_buf(_in_chans[chan_idx], process_frame.nframes),
		//sizeof (Audio::sample_t) * process_frame.nframes);
}
