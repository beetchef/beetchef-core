#include "jack_client_wrapper.hpp"
#include <jack/jack.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

using std::cerr;
using std::cout;
using std::endl;

#define LOG_LABEL "[JACK client wrapper]: "


Jack_client_wrapper::Jack_client_wrapper() {

    const char **ports;
	const char *client_name = "beetchef";
	const char *server_name = NULL;
	jack_options_t options = JackNullOption;
	jack_status_t status;

	/* open a client connection to the JACK server */
    _client = jack_client_open(client_name, options, &status, server_name);

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
		client_name = jack_get_client_name(_client);
		fprintf(stderr, "unique name `%s' assigned\n", client_name);
    }

    /* tell the JACK server to call `processCallbackStaticWrapper()' whenever
	   there is work to be done.
	*/

	jack_set_process_callback(_client, process_callback_static_wrapper, this);

	/* tell the JACK server to call `shutdownCallback()' if
	   it ever shuts down, either entirely, or if it
	   just decides to stop calling us.
	*/

	jack_on_shutdown(_client, shutdown_callback, 0);


	/* display the current sample rate.
	 */

    cout << LOG_LABEL << "created..." << endl;
    cout << LOG_LABEL << "sample rate: " << jack_get_sample_rate(_client) << "Hz" << endl;

}

Jack_client_wrapper::~Jack_client_wrapper() {
    if (_client) {
        jack_deactivate(_client);
        jack_client_close(_client);
    }
}

void Jack_client_wrapper::register_connection_node(Jack_connection_node *connection_node) {
    _connection_nodes.push_back(connection_node);
}

bool Jack_client_wrapper::activate() {

    //cout << mClient << endl;

    if (!_client) {
        cerr << LOG_LABEL << "Cannot activate JACK client, it's not open." << endl;
        return false;
    }
    jack_activate(_client);

    // jack_activate returns zero on success, non-zero otherwise
    if (jack_activate(_client)) {
        cerr << LOG_LABEL << "Failed to activate JACK client." << endl;
        return false;
    }

    return true;
}

bool Jack_client_wrapper::deactivate() {
    if (!_client) {
        cerr << LOG_LABEL << "Cannot deactivate JACK client, it's not open." << endl;
        return false;
    }

    // jack_deactivate returns zero on success, non-zero otherwise
    if (jack_deactivate(_client)) {
        cerr << LOG_LABEL << "Failed to deactivate JACK client." << endl;
        return false;
    }

    return true;
}

bool Jack_client_wrapper::create_port(string port_name, PortType port_type) {

    jack_port_t *port = jack_port_register (_client, port_name.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 port_type == INPUT_PORT ? JackPortIsInput : JackPortIsOutput, 0);

    if ((port == NULL)) {
		cerr << LOG_LABEL << "Failed to create " << (port_type == INPUT_PORT ? "input" : "output") << " port. No more JACK ports available." << endl;
		return false;
	}

    return true;
}

bool Jack_client_wrapper::create_input_port(string port_name) {

    jack_port_t *input_port = jack_port_register (_client, port_name.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsInput, 0);

    if ((input_port == NULL)) {
		cerr << LOG_LABEL << "Failed to create input port. No more JACK ports available." << endl;
		return false;
	}

    return true;
}

bool Jack_client_wrapper::create_output_port(string port_name) {

    jack_port_t *input_port = jack_port_register (_client, port_name.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsInput, 0);

    if ((input_port == NULL)) {
		cerr << LOG_LABEL << "Failed to create output port. No more JACK ports available." << endl;
		return false;
	}

    return true;
}

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client does nothing more than copy data from its input
 * port to its output port. It will exit when stopped by
 * the user (e.g. using Ctrl-C on a unix-ish operating system)
 */
int Jack_client_wrapper::process_callback_static_wrapper(jack_nframes_t nframes, void *arg) {
	/*jack_default_audio_sample_t *in, *out;

	in = jack_port_get_buffer (_nput_ports[0], nframes);
	out = jack_port_get_buffer (_utput_ports[0], nframes);
	memcpy (out, in,
		sizeof (jack_default_audio_sample_t) * nframes);

	return 0;*/
	return static_cast<Jack_client_wrapper*> (arg)->process_callback(nframes);
}

int Jack_client_wrapper::process_callback(jack_nframes_t nframes) {
	//jack_default_audio_sample_t *in, *out;

	//in = (jack_default_audio_sample_t *) jack_port_get_buffer (mInputPorts[0], nframes);
	//out =(jack_default_audio_sample_t *) jack_port_get_buffer (mOutputPorts[0], nframes);
	//memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);
    for (vector<Jack_connection_node *>::iterator connection_node = _connection_nodes.begin(); connection_node != _connection_nodes.end(); ++connection_node) {
        (*connection_node)->jack_process_callback(nframes);
    }
	return 0;
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void Jack_client_wrapper::shutdown_callback(void *arg) {
	cerr << LOG_LABEL << "Client was shut down by Jack." << endl;
	return;
}

void Jack_client_wrapper::test_connect() {
    if (jack_connect(_client, "beetchef:master_out_1", "sooperlooper:common_in_1")) {
        cerr << LOG_LABEL << "cannot connect port" << endl;
    }
    if (jack_connect(_client, "sooperlooper:common_out_2", "system:playback_1")) {
        cerr << LOG_LABEL << "cannot connect port" << endl;
    }
}
