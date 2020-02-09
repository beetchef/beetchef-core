#ifndef BEETCHEF_JACK_CLIENT_HPP
#define BEETCHEF_JACK_CLIENT_HPP

#include "audio/audio_types.hpp"
#include "jack_port.hpp"

#include <memory>
#include <string>
#include <vector>
#include <jack/jack.h>
#include <jack/types.h>

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

        void activate();
        void deactivate();
        bool is_active();

        nframes_t get_sample_rate();

        Jack_port register_input_port(std::string port_name);
        Jack_port register_output_port(std::string port_name);
        int connect_ports(std::string src_client_name, std::string src_port_name, std::string dest_client_name, std::string dest_port_name);

        void set_process_callback(/* TBD */);
    protected:
    private:
        static constexpr std::string_view log_label{"[JACK client]: "};

        std::string _client_name;
        std::unique_ptr<jack_client_t, Client_handle_deleter> _client;
        bool _active{false};
        /* TBD _process_callback; */

        Jack_client(std::string client_name, jack_status_t client_status);
        static int process_callback(jack_nframes_t nframes, void* arg);
        int process_nodes(jack_nframes_t nframes);
        static void shutdown_callback(void* arg);
};

#endif // BEETCHEF_JACK_CLIENT_HPP
