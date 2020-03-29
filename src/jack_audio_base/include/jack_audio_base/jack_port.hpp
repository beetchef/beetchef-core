#ifndef BEETCHEF_JACK_PORT_HANDLE_HPP
#define BEETCHEF_JACK_PORT_HANDLE_HPP

//#include "audio/audio_types.hpp"

#include <string>
#include <jack/jack.h>

enum class Port_type {
    input,
    output
};

class Jack_port {
    public:
        Jack_port(jack_client_t*, std::string port_name, Port_type port_type);
        Jack_port(const Jack_port&) = delete;
        Jack_port(Jack_port&&);
        Jack_port& operator=(const Jack_port&) = delete;
        Jack_port& operator=(Jack_port&&);
        ~Jack_port();

        jack_default_audio_sample_t* get_buffer(jack_nframes_t nframes) const;
    private:
        jack_client_t* _client;
        jack_port_t* _port;
};

#endif // BEETCHEF_JACK_PORT_HANDLE_HPP
