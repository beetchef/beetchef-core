#include "track.hpp"

#include "audio/audio_interface.hpp"

#include <algorithm>
#include <cstring>
#include <string>

Track::Track(Audio_interface* const audio_interface, const std::vector<int> in_chans, const std::string name)
    : _audio_interface{audio_interface}
    , _in_chans{in_chans}
    , _name{name}
{
}

void
Track::produce_to(const int chan_idx, const Process_frame& process_frame, sample_t* out_buf)
{
    sample_t* in_buf = _audio_interface->get_in_buf(_in_chans[chan_idx], process_frame.nframes);

    //std::copy(in_buf, in_buf + process_frame.nframes, out_buf);

    // seems to perform better
    std::memcpy(out_buf, _audio_interface->get_in_buf(_in_chans[chan_idx], process_frame.nframes),
		sizeof (sample_t) * process_frame.nframes);
}
