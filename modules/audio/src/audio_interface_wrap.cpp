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

using Audio::Audio_interface_wrap;

void Audio_interface_wrap::start_processing()
{
    _audio_interface->start_processing();
}

void Audio_interface_wrap::stop_processing()
{
    _audio_interface->stop_processing();
}

Audio::nframes_t Audio_interface_wrap::get_sample_rate() const
{
    return _audio_interface->get_sample_rate();
}

int Audio_interface_wrap::get_in_chan_count() const
{
    return _audio_interface->get_in_chan_count();
}

int Audio_interface_wrap::get_out_chan_count() const
{
    return _audio_interface->get_out_chan_count();
}

Audio::sample_t* Audio_interface_wrap::get_in_buf(int chan_idx, nframes_t nframes_t) const
{
    return _audio_interface->get_in_buf(chan_idx, nframes_t);
}

Audio::sample_t* Audio_interface_wrap::get_out_buf(int chan_idx, nframes_t nframes_t) const
{
    return _audio_interface->get_out_buf(chan_idx, nframes_t);
}

void Audio_interface_wrap::unregister_process_callback()
{
    _callback = Callback_function{dummy_callback};
}
