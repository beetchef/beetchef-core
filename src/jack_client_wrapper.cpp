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


JackClientWrapper::JackClientWrapper() {

    const char **ports;
	const char *client_name = "beetchef";
	const char *server_name = NULL;
	jack_options_t options = JackNullOption;
	jack_status_t status;

	/* open a client connection to the JACK server */
    mClient = jack_client_open (client_name, options, &status, server_name);
    if (mClient == NULL) {
		fprintf (stderr, "jack_client_open() failed, "
			 "status = 0x%2.0x\n", status);
		if (status & JackServerFailed) {
			fprintf (stderr, "Unable to connect to JACK server\n");
		}
		exit (1);
	}

	if (status & JackServerStarted) {
		fprintf (stderr, "JACK server started\n");
	}

	if (status & JackNameNotUnique) {
		client_name = jack_get_client_name(mClient);
		fprintf (stderr, "unique name `%s' assigned\n", client_name);
    }

    /* tell the JACK server to call `processCallbackStaticWrapper()' whenever
	   there is work to be done.
	*/

	jack_set_process_callback (mClient, processCallbackStaticWrapper, this);

	/* tell the JACK server to call `shutdownCallback()' if
	   it ever shuts down, either entirely, or if it
	   just decides to stop calling us.
	*/

	jack_on_shutdown (mClient, shutdownCallback, 0);


	/* display the current sample rate.
	 */

    cout << LOG_LABEL << "created..." << endl;
    cout << LOG_LABEL << "sample rate: " << jack_get_sample_rate(mClient) << "Hz" << endl;

}

JackClientWrapper::~JackClientWrapper() {
    if (mClient) {
        jack_deactivate(mClient);
        jack_client_close(mClient);
    }
}

void JackClientWrapper::registerConnectionNode(JackConnectionNode *connectionNode) {
    mConnectionNodes.push_back(connectionNode);
}

bool JackClientWrapper::activate() {

    //cout << mClient << endl;

    if (!mClient) {
        cerr << LOG_LABEL << "Cannot activate JACK client, it's not open." << endl;
        return false;
    }
    jack_activate(mClient);

    // jack_activate returns zero on success, non-zero otherwise
    if (jack_activate(mClient)) {
        cerr << LOG_LABEL << "Failed to activate JACK client." << endl;
        return false;
    }

    return true;
}

bool JackClientWrapper::deactivate() {
    if (!mClient) {
        cerr << LOG_LABEL << "Cannot deactivate JACK client, it's not open." << endl;
        return false;
    }

    // jack_deactivate returns zero on success, non-zero otherwise
    if (jack_deactivate(mClient)) {
        cerr << LOG_LABEL << "Failed to deactivate JACK client." << endl;
        return false;
    }

    return true;
}

bool JackClientWrapper::createPort(string portName, PortType portType) {

    jack_port_t *port = jack_port_register (mClient, portName.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 portType == inputPort ? JackPortIsInput : JackPortIsOutput, 0);

    if ((port == NULL)) {
		cerr << LOG_LABEL << "Failed to create " << (portType == inputPort ? "input" : "output") << " port. No more JACK ports available." << endl;
		return false;
	}

    return true;
}

bool JackClientWrapper::createInputPort(string portName) {

    jack_port_t *inputPort = jack_port_register (mClient, portName.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsInput, 0);

    if ((inputPort == NULL)) {
		cerr << LOG_LABEL << "Failed to create input port. No more JACK ports available." << endl;
		return false;
	}

    return true;
}

bool JackClientWrapper::createOutputPort(string portName) {

    jack_port_t *inputPort = jack_port_register (mClient, portName.c_str(),
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsInput, 0);

    if ((inputPort == NULL)) {
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
int JackClientWrapper::processCallbackStaticWrapper(jack_nframes_t nframes, void *arg) {
	/*jack_default_audio_sample_t *in, *out;

	in = jack_port_get_buffer (mInput_ports[0], nframes);
	out = jack_port_get_buffer (mOutput_ports[0], nframes);
	memcpy (out, in,
		sizeof (jack_default_audio_sample_t) * nframes);

	return 0;*/
	return static_cast<JackClientWrapper*> (arg)->processCallback(nframes);
}

int JackClientWrapper::processCallback(jack_nframes_t nframes) {
	//jack_default_audio_sample_t *in, *out;

	//in = (jack_default_audio_sample_t *) jack_port_get_buffer (mInputPorts[0], nframes);
	//out =(jack_default_audio_sample_t *) jack_port_get_buffer (mOutputPorts[0], nframes);
	//memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);
    for (vector<JackConnectionNode *>::iterator connectionNode = mConnectionNodes.begin(); connectionNode != mConnectionNodes.end(); ++connectionNode) {
        (*connectionNode)->jackProcessCallback(nframes);
    }
	return 0;
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void JackClientWrapper::shutdownCallback(void *arg) {
	cerr << LOG_LABEL << "Client was shut down by Jack." << endl;
	return;
}
