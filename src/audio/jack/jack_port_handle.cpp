#include "jack_port_handle.hpp"

#include <string>
#include <jack/jack.h>

Jack_port_handle::Jack_port_handle(jack_client_t* client, std::string port_name, Port_type port_type)
    : _client{client}
    , _port{jack_port_register(
                _client,
                port_name.c_str(),
                JACK_DEFAULT_AUDIO_TYPE,
                port_type == Port_type::input
                    ? JackPortIsInput
                    : JackPortIsOutput, 0)}
{
}

// move constructor
Jack_port_handle::Jack_port_handle(Jack_port_handle&& other)
    : _client{other._client}
    , _port{other._port}
{
    other._port = nullptr;
}

// move assignment
Jack_port_handle& Jack_port_handle::operator=(Jack_port_handle&& other)
{
    _client = other._client;
    _port = other._port;
    return *this;
}

Jack_port_handle::~Jack_port_handle()
{
    if(_client && _port) jack_port_unregister(_client, _port);
}

jack_port_t* Jack_port_handle::get()
{
    return _port;
}

sample_t* Jack_port_handle::get_buffer(nframes_t nframes)
{
    return static_cast<sample_t *>(jack_port_get_buffer(_port, nframes));
}
