#ifndef JACK_CONNECTION_NODE_HPP
#define JACK_CONNECTION_NODE_HPP

#include <vector>
#include "jack/jack.h"

using std::vector;

class JackConnectionNode {
    public:
        JackConnectionNode();
        ~JackConnectionNode();
        virtual void jackProcessCallback(jack_nframes_t nframes) = 0;
    protected:
        vector<jack_port_t *> mInputPorts;
        vector<jack_port_t *> mOutputPorts;
};

#endif // JACK_CONNECTION_NODE_HPP
