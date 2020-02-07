#ifndef BEETCHEF_JACK_PORT_HANDLE_HPP
#define BEETCHEF_JACK_PORT_HANDLE_HPP

#include "audio/audio_types.hpp"

#include <string>
#include <jack/jack.h>

enum class Port_type {
    input,
    output
};

class Jack_port_handle {
    public:
        Jack_port_handle(jack_client_t*, std::string port_name, Port_type port_type);
        Jack_port_handle(const Jack_port_handle&) = delete;
        Jack_port_handle(Jack_port_handle&&);
        Jack_port_handle& operator=(const Jack_port_handle&) = delete;
        Jack_port_handle& operator=(Jack_port_handle&&);
        ~Jack_port_handle();
        /* inline ? */jack_port_t* get();
        sample_t* get_buffer(nframes_t nframes);
    private:
        jack_client_t* _client;
        jack_port_t* _port;
};

#endif // BEETCHEF_JACK_PORT_HANDLE_HPP
