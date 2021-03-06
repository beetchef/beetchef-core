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

#include <jack_audio/jack_audio_interface.hpp>
#include <jack_audio/jack_client.hpp>

#include <memory>
#include <string>

using Jack_audio::Jack_audio_interface;
using Jack_audio::Jack_client;

Jack_audio_interface::Jack_audio_interface(Jack_client jack_client, int in_chan_count, int out_chan_count)
    : _jack_client{std::make_unique<Jack_client>(std::move(jack_client))}
{
    for (int i = 0; i < in_chan_count; i++) {
        std::string suffix = "_" + std::to_string(i + 1);
        _in_ports.push_back(_jack_client->register_input_port("main_in" + suffix));
    }
    for (int i = 0; i < out_chan_count; i++) {
        std::string suffix = "_" + std::to_string(i + 1);
        _out_ports.push_back(_jack_client->register_output_port("main_out" + suffix));
    }
}

void Jack_audio_interface::unset_process_callback()
{
    _jack_client->unset_process_callback();
}

void Jack_audio_interface::start_processing()
{
    _jack_client->activate();
    connect_io_ports();
}

void Jack_audio_interface::stop_processing()
{
    _jack_client->deactivate();
}

Jack_client* Jack_audio_interface::get_jack_client()
{
    return _jack_client.get();
}

jack_nframes_t Jack_audio_interface::get_sample_rate() const
{
    return _jack_client->get_sample_rate();
}

int Jack_audio_interface::get_in_chan_count() const
{
    return _in_ports.size();
}

int Jack_audio_interface::get_out_chan_count() const
{
    return _out_ports.size();
}

jack_default_audio_sample_t* Jack_audio_interface::get_in_buf(int chan_idx, jack_nframes_t nframes) const
{
    return _in_ports[chan_idx].get_buffer(nframes);
}

jack_default_audio_sample_t* Jack_audio_interface::get_out_buf(int chan_idx, jack_nframes_t nframes) const
{
    return _out_ports[chan_idx].get_buffer(nframes);
}

void Jack_audio_interface::connect_io_ports() const
{
    for (std::size_t i = 0; i < _in_ports.size(); i++) {
        std::string suffix = "_" + std::to_string(i + 1);
        _jack_client->connect_ports("system", "capture" + suffix, "beetchef", "main_in" + suffix);
    }
    for (std::size_t i = 0; i < _out_ports.size(); i++) {
        std::string suffix = "_" + std::to_string(i + 1);
        _jack_client->connect_ports("beetchef", "main_out" + suffix, "system", "playback" + suffix);
    }
}
