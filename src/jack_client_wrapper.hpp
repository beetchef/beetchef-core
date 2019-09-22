#ifndef JACK_WRAPPER_HPP
#define JACK_WRAPPER_HPP

#include "jack/jack.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

enum PortType {
    inputPort,
    outputPort
};

class JackClientWrapper {
    public:
        JackClientWrapper();
        ~JackClientWrapper();
        bool activate();
        bool deactivate();
        bool createPort(string portName, PortType portType);
        bool createInputPort(string portName);
        bool createOutputPort(string portName);
    protected:
    private:
        vector<jack_port_t *> mInputPorts;
        vector<jack_port_t *> mOutputPorts;
        jack_client_t *mClient = 0;
        static int processCallbackStaticWrapper(jack_nframes_t nframes, void *arg);
        int processCallback(jack_nframes_t nframes);
        static void shutdownCallback(void *arg);
};

#endif // JACK_WRAPPER_HPP
