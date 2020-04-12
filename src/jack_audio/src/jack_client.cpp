#include <jack_audio/jack_client.hpp>
#include <jack_audio/jack_error.hpp>
#include <jack_audio/jack_port.hpp>

#include <memory>
#include <string>

#include <jack/jack.h>
#include <jack/types.h>

#include <spdlog/spdlog.h>

using Jack_audio::Client_handle_deleter;
using Jack_audio::Jack_client;
using Jack_audio::Jack_port;

/**
 * Custom deleter for unique_ptr owning jack_client_t pointer
 */
void Client_handle_deleter::operator()(jack_client_t* client_ptr) const
{
    // deactivate jack client, unregister all ports
    int res_code = jack_deactivate(client_ptr);
    if (res_code)
        spdlog::error("{} Failed to deactivate JACK client, error code = {}", Jack_client::log_label, res_code);

    // within jack_client_close() a "delete" keyword is used to free the memory
    // used by jack client object on the heap
    res_code = jack_client_close(client_ptr);
    if (res_code)
        spdlog::error("{} Failed to close JACK client, error code = {}", Jack_client::log_label, res_code);
}

/**
 * Public delegating constructor only calls private parametrized constructor
 * with some value of jack_status_t enum. It doesn't matter which value - this
 * is only done so the other constructor has an initialized variable to write
 * jack status to when calling jack_client_open() within member initializer list.
 */
Jack_client::Jack_client(std::string client_name)
    : Jack_client(client_name, JackInitFailure)
{
}

/**
 * Private constructor is called with client_status parameter which is in turn
 * used to write jack status to when calling jack_client_open() within member
 * initializer list - therefore the value of the parameter doesn't matter.
 */
Jack_client::Jack_client(std::string client_name, jack_status_t client_status)
    : _client_name{client_name}
    , _client{
        // within jack_client_open() a "new" keyword is used to allocate jack client object
        // on the heap thus jack_client_t* returned from the function is an owning pointer
        jack_client_open(_client_name.c_str(), JackNullOption, &client_status),
        // this custom deleter calls jack_client_close() to delete the owning pointer
        Client_handle_deleter{}}
{

    if (_client == NULL)
    {
        throw Jack_error{
            "Failed to create JACK client, status = "
                + std::to_string(client_status)
                + std::string(
                    client_status & JackServerFailed
                        ? ", unable to connect to JACK server."
                        : ".")
        };
	}

	if (client_status & JackServerStarted)
        spdlog::info("{} JACK server started.", log_label);

	if (client_status & JackNameNotUnique)
        spdlog::info("{} Unique name {} assigned.", log_label, jack_get_client_name(_client.get()));
		
	jack_on_shutdown(_client.get(), shutdown_callback, 0);

    spdlog::info("{} Created.", log_label);
}

void Jack_client::unset_process_callback()
{
    int res_code = jack_set_process_callback(_client.get(), nullptr, nullptr);

    if (res_code)
    {
        throw Jack_error{"Failed to unset process callback, error code = " + std::to_string(res_code) + "."};
    }
    else
    {
        spdlog::info("{} Process callback unset.", log_label);
    }
}

void Jack_client::activate()
{
    int res_code = jack_activate(_client.get());

    if (res_code)
    {
        throw Jack_error{"Failed to activate JACK client, error code = " + std::to_string(res_code) + ". Maybe JACK client is active?"};
    }
    else
    {
        _active = true;
        spdlog::info("{} Activated.", log_label);
    }
}


void Jack_client::deactivate()
{
    int res_code = jack_deactivate(_client.get());

    if (res_code)
    {
        throw Jack_error{"Failed to deactivate JACK client, error code = " + std::to_string(res_code) + "."};
    }
    else
    {
        _active = false;
        spdlog::info("{} Deactivated.", log_label);
    }
}

Jack_port Jack_client::register_input_port(std::string port_name)
{
    return Jack_port{_client.get(), port_name, Port_type::input};
}

Jack_port Jack_client::register_output_port(std::string port_name)
{
    return Jack_port{_client.get(), port_name, Port_type::output};
}

void Jack_client::connect_ports(std::string src_client_name, std::string src_port_name, std::string dest_client_name, std::string dest_port_name)
{
    std::string src_full_name = src_client_name + ":" + src_port_name;
    std::string dest_full_name = dest_client_name + ":" + dest_port_name;
    int res_code = jack_connect(_client.get(), src_full_name.c_str(), dest_full_name.c_str());

    if(res_code)
    {
        throw Jack_error{
            "Failed to connect port " + src_full_name
                + " with port " + dest_full_name
                + ", error code = " + std::to_string(res_code) + ". "
                + "Maybe JACK client is not activated?"
        };
    }
}

bool Jack_client::is_active()
{
    return _active;
}

jack_nframes_t Jack_client::get_sample_rate() const
{
    return jack_get_sample_rate(_client.get());
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void Jack_client::shutdown_callback(void* arg)
{
	throw Jack_error{"Client was shut down by JACK."};
}
