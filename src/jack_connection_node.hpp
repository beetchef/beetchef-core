#ifndef JACK_CONNECTION_NODE_HPP
#define JACK_CONNECTION_NODE_HPP

#include <vector>
#include "jack/jack.h"

using std::vector;

class JackConnectionNode {
    public:
        JackConnectionNode();
        ~JackConnectionNode();
        virtual void jack_process_callback(jack_nframes_t nframes) = 0;
    protected:
        vector<jack_port_t *> _input_ports;
        vector<jack_port_t *> _output_ports;
};

#endif // JACK_CONNECTION_NODE_HPP
