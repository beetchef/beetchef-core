#ifndef JACK_WRAPPER_HPP
#define JACK_WRAPPER_HPP

#include "audio/audio_types.hpp"
#include "jack_port_handle.hpp"

#include <memory>
#include <string>
#include <vector>
#include <jack/jack.h>
#include <jack/types.h>

struct Jack_client_deleter {
    void operator()(jack_client_t* client_ptr) const;
};

class Jack_client_wrapper {
    public:
        Jack_client_wrapper();
        Jack_client_wrapper(const Jack_client_wrapper&) = delete;
        Jack_client_wrapper(Jack_client_wrapper&&) = default;
        Jack_client_wrapper& operator=(const Jack_client_wrapper&) = delete;
        Jack_client_wrapper& operator=(Jack_client_wrapper&&) = default;
        ~Jack_client_wrapper() = default;
        Jack_port_handle register_input_port(std::string port_name);
        Jack_port_handle register_output_port(std::string port_name);
        void set_process_callback(/* TBD */);
        void test_connect();
        void test(Jack_port_handle bla) {};
    protected:
    private:
        static constexpr std::string_view log_label{"[JACK client wrapper]: "};
        inline static const std::string _client_name{"beetchef"};
        std::vector<jack_port_t*> _input_ports;
        std::vector<jack_port_t*> _output_ports;
        std::unique_ptr<jack_client_t, Jack_client_deleter> _client;
        /* TBD _process_callback; */
        Jack_client_wrapper(jack_status_t client_status);
        static int process_callback(jack_nframes_t nframes, void* arg);
        int process_nodes(jack_nframes_t nframes);
        static void shutdown_callback(void* arg);
};

#endif // JACK_CLIENT_WRAPPER_HPP
