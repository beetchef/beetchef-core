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

#ifndef BEETCHEF_JACK_PORT_HANDLE_HPP
#define BEETCHEF_JACK_PORT_HANDLE_HPP

#include <string>
#include <jack/jack.h>

namespace Jack_audio
{
    enum class Port_type {
        input,
        output
    };

    class Jack_port {
        public:
            Jack_port(jack_client_t*, std::string port_name, Port_type port_type);
            Jack_port(const Jack_port&) = delete;
            Jack_port(Jack_port&&);
            Jack_port& operator=(const Jack_port&) = delete;
            Jack_port& operator=(Jack_port&&);
            ~Jack_port();

            jack_default_audio_sample_t* get_buffer(jack_nframes_t nframes) const;
        private:
            jack_client_t* _client;
            jack_port_t* _port;
    };

}; // namespace Jack_audio

#endif // BEETCHEF_JACK_PORT_HANDLE_HPP
