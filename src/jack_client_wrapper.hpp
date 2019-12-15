#ifndef JACK_WRAPPER_HPP
#define JACK_WRAPPER_HPP

#include "jack/jack.h"
#include "jack_connection_node.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

enum PortType {
    INPUT_PORT,
    OUTPUT_PORT
};

class JackClientWrapper {
    public:
        JackClientWrapper();
        ~JackClientWrapper();
        void register_connection_node(JackConnectionNode *connection_node);
        bool activate();
        bool deactivate();
        bool create_port(string port_name, PortType port_type);
        bool create_input_port(string port_name);
        bool create_output_port(string port_name);
        void test_connect();
    protected:
    private:
        vector<jack_port_t *> _input_ports;
        vector<jack_port_t *> _output_ports;
        vector<JackConnectionNode *> _connection_nodes;
        jack_client_t *_client = 0;
        static int process_callback_static_wrapper(jack_nframes_t nframes, void *arg);
        int process_callback(jack_nframes_t nframes);
        static void shutdown_callback(void *arg);
};

#endif // JACK_WRAPPER_HPP
