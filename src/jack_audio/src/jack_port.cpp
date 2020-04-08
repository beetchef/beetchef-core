#include "jack_audio/jack_error.hpp"
#include "jack_audio/jack_port.hpp"

#include <sstream>
#include <string>
#include <jack/jack.h>

Jack_port::Jack_port(jack_client_t* client, std::string port_name, Port_type port_type)
    : _client{client}
    , _port{jack_port_register(
                _client,
                port_name.c_str(),
                JACK_DEFAULT_AUDIO_TYPE,
                port_type == Port_type::input
                    ? JackPortIsInput
                    : JackPortIsOutput,
                0)}
{
    if (!_port)
    {
        std::stringstream msg_buf;
        msg_buf << "Failed to register JACK "
            << (port_type == Port_type::input ? "input " : "output ")
            << "port: "
            << port_name
            << ".";

        throw Jack_error{msg_buf.str()};
    }
}

// move constructor
Jack_port::Jack_port(Jack_port&& other)
    : _client{other._client}
    , _port{other._port}
{
    other._port = nullptr;
}

// move assignment
Jack_port& Jack_port::operator=(Jack_port&& other)
{
    _client = other._client;
    _port = other._port;
    return *this;
}

Jack_port::~Jack_port()
{
    if (_client && _port) jack_port_unregister(_client, _port);
}

jack_default_audio_sample_t* Jack_port::get_buffer(jack_nframes_t nframes) const
{
    return static_cast<jack_default_audio_sample_t *>(jack_port_get_buffer(_port, nframes));
}
