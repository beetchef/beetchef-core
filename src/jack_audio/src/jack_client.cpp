#include "jack_audio/jack_client.hpp"
#include "jack_audio/jack_error.hpp"
#include "jack_audio/jack_port.hpp"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>
#include <unistd.h>
#include <jack/jack.h>
#include <jack/types.h>

/**
 * Custom deleter for unique_ptr owning jack_client_t pointer
 */
void Client_handle_deleter::operator()(jack_client_t* client_ptr) const
{
    // deactivate jack client, unregister all ports
    int res_code = jack_deactivate(client_ptr);
    if (res_code)
        std::cerr << Jack_client::log_label << "Failed to deactivate JACK client, error code = " << std::to_string(res_code) << std::endl;

    // within jack_client_close() a "delete" keyword is used to free the memory
    // used by jack client object on the heap
    res_code = jack_client_close(client_ptr);
    if (res_code)
        std::cerr << Jack_client::log_label << "Failed to close JACK client, error code = " << std::to_string(res_code) << std::endl;
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
        std::stringstream msg_buf;
        msg_buf << "Failed to create JACK client, status = "
            << client_status
            << ((client_status & JackServerFailed)
                ? ", unable to connect to JACK server."
                : ".");

		throw Jack_error{msg_buf.str()};
	}

	if (client_status & JackServerStarted)
        std::cout << log_label << "JACK server started." << std::endl;

	if (client_status & JackNameNotUnique)
		std::cout << log_label << "Unique name " << jack_get_client_name(_client.get()) << " assigned." << std::endl;

	jack_on_shutdown(_client.get(), shutdown_callback, 0);

    std::cout << log_label << "Created..." << std::endl;
}

bool Jack_client::unset_process_callback()
{
    int res_code = jack_set_process_callback(_client.get(), nullptr, nullptr);

    if (res_code)
        std::cerr << log_label << "Failed to unset process callback, error code = " << std::to_string(res_code) << "." << std::endl;
    else
        std::cout << log_label << "Process callback unset..." << std::endl;

    return !res_code;
}

bool Jack_client::activate()
{
    int res_code = jack_activate(_client.get());

    if (res_code)
    {
        std::cerr << log_label << "Failed to activate JACK client, error code = " << std::to_string(res_code) << "." << std::endl;
    }
    else
    {
        _active = true;
        std::cout << log_label << "Activated..." << std::endl;
    }

    return !res_code;
}


bool Jack_client::deactivate()
{
    int res_code = jack_deactivate(_client.get());

    if (res_code)
    {
        std::cerr << log_label << "Failed to deactivate JACK client, error code = " << std::to_string(res_code) << "." << std::endl;
    }
    else
    {
        _active = false;
        std::cout << log_label << "Deactivated..." << std::endl;
    }

    return !res_code;
}

Jack_port Jack_client::register_input_port(std::string port_name)
{
    return Jack_port{_client.get(), port_name, Port_type::input};
}

Jack_port Jack_client::register_output_port(std::string port_name)
{
    return Jack_port{_client.get(), port_name, Port_type::output};
}

bool Jack_client::connect_ports(std::string src_client_name, std::string src_port_name, std::string dest_client_name, std::string dest_port_name)
{
    std::string src_full_name = src_client_name + ":" + src_port_name;
    std::string dest_full_name = dest_client_name + ":" + dest_port_name;
    int res_code = jack_connect(_client.get(), src_full_name.c_str(), dest_full_name.c_str());

    if(res_code)
    {
        std::cerr
            << log_label
            << "Failed to connect port " << src_full_name
            << " with port " << dest_full_name
            << ", error code = " << std::to_string(res_code)
            << "." << std::endl;
    }

    return res_code;
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
	std::cerr << log_label << "Client was shut down by Jack." << std::endl;
	return;
}
