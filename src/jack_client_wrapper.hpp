#ifndef JACK_WRAPPER_HPP
#define JACK_WRAPPER_HPP

#include "jack_connection_node.hpp"

#include <memory>
#include <string>
#include <vector>
#include <jack/jack.h>

enum class PortType {
    input,
    output
};

struct Jack_client_deleter {
    void operator()(jack_client_t* client_ptr) const;
};

class Jack_client_wrapper {
    public:
        Jack_client_wrapper();
        void register_connection_node(Jack_connection_node* connection_node);
        bool activate();
        bool create_port(std::string port_name, PortType port_type);
        bool create_input_port(std::string port_name);
        bool create_output_port(std::string port_name);
        void test_connect();
    protected:
    private:
        static constexpr std::string_view log_label{"[JACK client wrapper]: "};
        inline static const std::string _client_name{"beetchef"};
        std::vector<jack_port_t*> _input_ports;
        std::vector<jack_port_t*> _output_ports;
        std::vector<Jack_connection_node*> _connection_nodes;
        jack_status_t _client_status;
        std::unique_ptr<jack_client_t, Jack_client_deleter> _client;
        static int process_callback(jack_nframes_t nframes, void* arg);
        int process_nodes(jack_nframes_t nframes);
        static void shutdown_callback(void* arg);
};

#endif // JACK_CLIENT_WRAPPER_HPP
