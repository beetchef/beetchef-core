/*
 *  Beetchef - real time audio sequencer
 *  Copyright (C) 2020 Anton Šefčík
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <audio/audio_interface_wrap.hpp>
#include <audio/types.hpp>

#include <processing/track.hpp>
#include <processing/types.hpp>

#include <algorithm>
#include <cstring>
#include <string>

using Processing::Track;

Track::Track(const std::string name, const std::vector<int> in_chans, Audio::Audio_interface_wrap* const audio_interface)
    : _name{name}
    , _in_chans{in_chans}
    , _audio_interface{audio_interface}
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
