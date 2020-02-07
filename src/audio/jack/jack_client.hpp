#ifndef BEETCHEF_JACK_CLIENT_HPP
#define BEETCHEF_JACK_CLIENT_HPP

#include "audio/audio_types.hpp"
#include "jack_port_handle.hpp"

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
        Jack_client();
        Jack_client(const Jack_client&) = delete;
        Jack_client(Jack_client&&) = default;
        Jack_client& operator=(const Jack_client&) = delete;
        Jack_client& operator=(Jack_client&&) = default;
        ~Jack_client() = default;
        nframes_t get_sample_rate();
        Jack_port_handle register_input_port(std::string port_name);
        Jack_port_handle register_output_port(std::string port_name);
        void set_process_callback(/* TBD */);
        void test_connect();
        void test(Jack_port_handle bla) {};
    protected:
    private:
        static constexpr std::string_view log_label{"[JACK client]: "};
        inline static const std::string _client_name{"beetchef"};
        std::vector<jack_port_t*> _input_ports;
        std::vector<jack_port_t*> _output_ports;
        std::unique_ptr<jack_client_t, Client_handle_deleter> _client_handle;
        /* TBD _process_callback; */
        Jack_client(jack_status_t client_status);
        static int process_callback(jack_nframes_t nframes, void* arg);
        int process_nodes(jack_nframes_t nframes);
        static void shutdown_callback(void* arg);
};

#endif // BEETCHEF_JACK_CLIENT_HPP
