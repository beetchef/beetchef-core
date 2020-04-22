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

#include <jack_audio/jack_error.hpp>
#include <jack_audio/jack_port.hpp>

#include <string>
#include <jack/jack.h>

using Jack_audio::Jack_port;

Jack_port::Jack_port(jack_client_t* client, std::string port_name, Port_type port_type)
    : _client{client}
    , _port{jack_port_register(
                _client,
                port_name.c_str(),
                JACK_DEFAULT_AUDIO_TYPE,
                port_type == Port_type::input
                    ? JackPortIsInput
                    : JackPortIsOutput,
                0)}
{
    if (!_port)
    {
        throw Jack_error{
            "Failed to register JACK "
                + std::string(port_type == Port_type::input ? "input " : "output ")
                + "port: "
                + port_name
                + "."
        };
    }
}

// move constructor
Jack_port::Jack_port(Jack_port&& other)
    : _client{other._client}
    , _port{other._port}
{
    other._port = nullptr;
}

// move assignment
Jack_port& Jack_port::operator=(Jack_port&& other)
{
    _client = other._client;
    _port = other._port;
    return *this;
}

Jack_port::~Jack_port()
{
    if (_client && _port) jack_port_unregister(_client, _port);
}

jack_default_audio_sample_t* Jack_port::get_buffer(jack_nframes_t nframes) const
{
    return static_cast<jack_default_audio_sample_t *>(jack_port_get_buffer(_port, nframes));
}
