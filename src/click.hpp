#ifndef CLICK_HPP
#define CLICK_HPP

#include "jack_connection_node.hpp"
#include "messaging_handler.hpp"
#include "jack_client_wrapper.hpp"

class Click: public JackConnectionNode {
    public:
        Click(unsigned int tempo, unsigned int signature_numerator, unsigned int signature_denominator);
        bool initialize(JackClientWrapper *jack_client_wrapper);
        void start();
        void jack_process_callback(jack_nframes_t nframes);
    protected:
    private:
        JackClientWrapper *_jack_client_wrapper;
        unsigned int _tempo;
        unsigned int _signature_numerator;
        unsigned int _signature_denominator;
        unsigned int _current_beat;
        long _beat_duration;
        long _bar_duration;
        bool _is_running;
        MessagingHandler _messaging_handler;
};

#endif
