#ifndef JACK_WRAPPER_HPP
#define JACK_WRAPPER_HPP

#include "jack/jack.h"
#include "jack_connection_node.hpp"
#include <string>
#include <vector>

enum PortType {
    INPUT_PORT,
    OUTPUT_PORT
};

class Jack_client_wrapper {
    public:
        Jack_client_wrapper();
        ~Jack_client_wrapper();
        void register_connection_node(Jack_connection_node *connection_node);
        bool activate();
        bool deactivate();
        bool create_port(std::string port_name, PortType port_type);
        bool create_input_port(std::string port_name);
        bool create_output_port(std::string port_name);
        void test_connect();
    protected:
    private:
        std::vector<jack_port_t *> _input_ports;
        std::vector<jack_port_t *> _output_ports;
        std::vector<Jack_connection_node *> _connection_nodes;
        jack_client_t *_client = 0;
        static int process_callback_static_wrapper(jack_nframes_t nframes, void *arg);
        int process_callback(jack_nframes_t nframes);
        static void shutdown_callback(void *arg);
};

#endif // JACK_WRAPPER_HPP
