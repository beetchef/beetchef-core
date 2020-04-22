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

#ifndef BEETCHEF_JACK_CLIENT_HPP
#define BEETCHEF_JACK_CLIENT_HPP

#include "jack_error.hpp"
#include "jack_audio/jack_port.hpp"

#include <memory>
#include <string>
#include <vector>

#include <jack/jack.h>
#include <jack/types.h>

#include <spdlog/spdlog.h>

namespace Jack_audio
{
    struct Client_handle_deleter {
        void operator()(jack_client_t* client_ptr) const;
    };

    class Jack_client {
        public:
            explicit Jack_client(std::string client_name = "beetchef");
            Jack_client(const Jack_client&) = delete;
            Jack_client(Jack_client&&) = default;
            Jack_client& operator=(const Jack_client&) = delete;
            Jack_client& operator=(Jack_client&&) = default;
            ~Jack_client() = default;

            template<typename T>
            void set_process_callback(T* callable)
            {
                int res_code = jack_set_process_callback(_client.get(), process_callback<T>, callable);

                if (res_code)
                {
                    throw Jack_error{"Failed to set process callback, error code = " + std::to_string(res_code) + ". Maybe JACK client is active?"};
                }
                else
                {
                    spdlog::info("{} Process callback set.", log_label);
                }
            }

            void unset_process_callback();

            void activate();
            void deactivate();

            Jack_port register_input_port(std::string port_name);
            Jack_port register_output_port(std::string port_name);
            void connect_ports(std::string src_client_name, std::string src_port_name, std::string dest_client_name, std::string dest_port_name);

            bool is_active();
            jack_nframes_t get_sample_rate() const;

        private:
            static constexpr std::string_view log_label{"[JACK client]"};
            friend struct Client_handle_deleter;

            std::string _client_name;
            std::unique_ptr<jack_client_t, Client_handle_deleter> _client;
            bool _active{false};

            Jack_client(std::string client_name, jack_status_t client_status);

            template<typename T>
            static int process_callback(jack_nframes_t nframes, void* callback)
            {
                return static_cast<T*>(callback)->operator()(nframes);
            }

            static void shutdown_callback(void* arg);
    };

}; // namespace Jack_audio

#endif // BEETCHEF_JACK_CLIENT_HPP
