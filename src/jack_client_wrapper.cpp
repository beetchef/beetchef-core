#include "jack_client_wrapper.hpp"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>
#include <jack/jack.h>

Jack_client_wrapper::Jack_client_wrapper()
{
    const char **ports;
	jack_options_t options = JackNullOption;
	jack_status_t status;

	// open a client connection to the JACK server
    _client = jack_client_open(_client_name.c_str(), options, &status);

    if (_client == NULL) {
		fprintf (stderr, "jack_client_open() failed, "
			 "status = 0x%2.0x\n", status);
		if (status & JackServerFailed) {
			fprintf(stderr, "Unable to connect to JACK server\n");
		}
		exit (1);
	}

	if (status & JackServerStarted) {
		fprintf(stderr, "JACK server started\n");
	}

	if (status & JackNameNotUnique) {
		auto client_name = jack_get_client_name(_client);
		fprintf(stderr, "unique name `%s' assigned\n", client_name);
    }

    jack_set_process_callback(_client, process_callback, this);

	jack_on_shutdown(_client, shutdown_callback, 0);

    std::cout << log_label << "created..." << std::endl;
    std::cout << log_label << "sample rate: " << jack_get_sample_rate(_client) << "Hz" << std::endl;
}

Jack_client_wrapper::~Jack_client_wrapper()
{
    if (_client) {
        jack_deactivate(_client);
        jack_client_close(_client);
    }
}

void Jack_client_wrapper::register_connection_node(Jack_connection_node *connection_node)
{
    _connection_nodes.push_back(connection_node);
}

bool Jack_client_wrapper::activate()
{
    //cout << mClient << endl;

    if (!_client) {
        std::cerr << log_label << "Cannot activate JACK client, it's not open." << std::endl;
        return false;
    }
    jack_activate(_client);

    // jack_activate returns zero on success, non-zero otherwise
    if (jack_activate(_client)) {
        std::cerr << log_label << "Failed to activate JACK client." << std::endl;
        return false;
    }

    return true;
}

bool Jack_client_wrapper::deactivate()
{
    if (!_client) {
        std::cerr << log_label << "Cannot deactivate JACK client, it's not open." << std::endl;
        return false;
    }

    // jack_deactivate returns zero on success, non-zero otherwise
    if (jack_deactivate(_client)) {
        std::cerr << log_label << "Failed to deactivate JACK client." << std::endl;
        return false;
    }

    return true;
}

bool Jack_client_wrapper::create_port(std::string port_name, PortType port_type)
{
    jack_port_t *port = jack_port_register (_client, port_name.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 port_type == PortType::input ? JackPortIsInput : JackPortIsOutput, 0);

    if ((port == NULL)) {
		std::cerr << log_label << "Failed to create " << (port_type == PortType::input ? "input" : "output") << " port. No more JACK ports available." << std::endl;
		return false;
	}

    return true;
}

bool Jack_client_wrapper::create_input_port(std::string port_name)
{
    jack_port_t* input_port = jack_port_register (_client, port_name.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsInput, 0);

    if ((input_port == NULL)) {
		std::cerr << log_label << "Failed to create input port. No more JACK ports available." << std::endl;
		return false;
	}

    return true;
}

bool Jack_client_wrapper::create_output_port(std::string port_name)
{
    jack_port_t* input_port = jack_port_register (_client, port_name.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsInput, 0);

    if ((input_port == NULL)) {
		std::cerr << log_label << "Failed to create output port. No more JACK ports available." << std::endl;
		return false;
	}

    return true;
}

/**
 * The process callback is called in a
 * special realtime thread once for each audio cycle.
 */
int Jack_client_wrapper::process_callback(jack_nframes_t nframes, void *arg)
{
	return static_cast<Jack_client_wrapper*> (arg)->process_nodes(nframes);
}

int Jack_client_wrapper::process_nodes(jack_nframes_t nframes)
{
	//jack_default_audio_sample_t *in, *out;

	//in = (jack_default_audio_sample_t *) jack_port_get_buffer (mInputPorts[0], nframes);
	//out =(jack_default_audio_sample_t *) jack_port_get_buffer (mOutputPorts[0], nframes);
	//memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);

    for (auto node : _connection_nodes) {
        node->jack_process_callback(nframes);
    }
	return 0;
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
    if (jack_connect(_client, "beetchef:master_out_1", "sooperlooper:common_in_1")) {
        std::cerr << log_label << "cannot connect port" << std::endl;
    }
    if (jack_connect(_client, "sooperlooper:common_out_2", "system:playback_1")) {
        std::cerr << log_label << "cannot connect port" << std::endl;
    }
}
