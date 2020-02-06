#include "audio/audio_types.hpp"
#include "beetchef_error.hpp"
#include "jack_client_wrapper.hpp"
#include "jack_port_handle.hpp"

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
void Jack_client_deleter::operator()(jack_client_t* client_ptr) const
{
    // deactivate jack client, unregister all ports
    jack_deactivate(client_ptr);
    // within jack_client_close() a "delete" keyword is used to free the memory
    // used by jack client object on the heap
    jack_client_close(client_ptr);
}

/**
 * Public delegating constructor only calls private parametrized constructor
 * with some value of jack_status_t enum. It doesn't matter which value - this
 * is only done so the other constructor has an initialized variable to write
 * jack status to when calling jack_client_open() within member initializer list.
 */
Jack_client_wrapper::Jack_client_wrapper()
    : Jack_client_wrapper{JackInitFailure}
{
}

/**
 * Private constructor is called with client_status parameter which is in turn
 * used to write jack status to when calling jack_client_open() within member
 * initializer list - therefore the value of the parameter doesn't matter.
 */
Jack_client_wrapper::Jack_client_wrapper(jack_status_t client_status)
    : _client{
        // within jack_client_open() a "new" keyword is used to allocate jack client object
        // on the heap thus jack_client_t* returned from the function is an owning pointer
        jack_client_open(_client_name.c_str(), JackNullOption, &client_status),
        // this custom deleter calls jack_client_close() to delete the owning pointer
        Jack_client_deleter{}}
{

    if (_client == NULL) {
        std::stringstream msg_buf;
        msg_buf << "Failed to create JACK client, status = "
            << client_status
            << ((client_status & JackServerFailed)
                ? ", unable to connect to JACK server."
                : ".");

		throw Beetchef_error{msg_buf.str()};
	}

	if (client_status & JackServerStarted)
        std::cout << log_label << "JACK server started." << std::endl;

	if (client_status & JackNameNotUnique)
		std::cerr << log_label << "Unique name " << jack_get_client_name(_client.get()) << " assigned." << std::endl;

    jack_set_process_callback(_client.get(), process_callback, this);

	jack_on_shutdown(_client.get(), shutdown_callback, 0);

    std::cout << log_label << "Created..." << std::endl;
    std::cout << log_label << "Sample rate: " << jack_get_sample_rate(_client.get()) << "Hz" << std::endl;

    int err_code = jack_activate(_client.get());

    if (err_code)
        throw Beetchef_error{"Failed to activate JACK client, error code = " + std::to_string(err_code) + "."};

    std::cout << log_label << "Activated..." << std::endl;
}

Jack_port_handle Jack_client_wrapper::register_input_port(std::string port_name)
{
    return Jack_port_handle{_client.get(), port_name, Port_type::input};
}

Jack_port_handle Jack_client_wrapper::register_output_port(std::string port_name)
{
    return Jack_port_handle{_client.get(), port_name, Port_type::output};
}

/**
 * The process callback is called in a
 * special realtime thread once for each audio cycle.
 */
int Jack_client_wrapper::process_callback(jack_nframes_t nframes, void *arg)
{
    // TODO: call registered _process_callback
	//return static_cast<Jack_client_wrapper*>(arg)->_process_callback(nframes);
	return 0;
}

void Jack_client_wrapper::set_process_callback(/* TBD */)
{
    // TODO: _process_callback = TBD;
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void Jack_client_wrapper::shutdown_callback(void* arg)
{
	std::cerr << log_label << "Client was shut down by Jack." << std::endl;
	return;
}

void Jack_client_wrapper::test_connect()
{
    if (jack_connect(_client.get(), "beetchef:master_out_1", "sooperlooper:common_in_1")) {
        std::cerr << log_label << "Cannot connect port." << std::endl;
    }
    if (jack_connect(_client.get(), "sooperlooper:common_out_2", "system:playback_1")) {
        std::cerr << log_label << "Cannot connect port." << std::endl;
    }
}
