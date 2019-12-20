#ifndef JACK_CONNECTION_NODE_HPP
#define JACK_CONNECTION_NODE_HPP

#include <vector>
#include <jack/jack.h>

class Jack_connection_node {
    public:
        Jack_connection_node();
        ~Jack_connection_node();
        virtual void jack_process_callback(jack_nframes_t nframes) = 0;
    protected:
        std::vector<jack_port_t *> _input_ports;
        std::vector<jack_port_t *> _output_ports;
};

#endif // JACK_CONNECTION_NODE_HPP
