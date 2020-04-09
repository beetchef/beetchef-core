#ifndef BEETCHEF_JACK_CLIENT_HPP
#define BEETCHEF_JACK_CLIENT_HPP

#include <jack_audio/jack_error.hpp>
#include <jack_audio/jack_port.hpp>

#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include <jack/jack.h>
#include <jack/types.h>

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
                    std::cout << log_label << "Process callback set..." << "\n";
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
            static constexpr std::string_view log_label{"[JACK client]: "};
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
