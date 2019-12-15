#include "engine.hpp"
#include "click.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using std::cerr;
using std::cout;
using std::endl;

#define LOG_LABEL "[Engine]: "

Engine::Engine() : _click(60, 4, 4) {
    _is_alive = true;
    cout << LOG_LABEL << "created..." << endl;
}

bool Engine::initialize(JackClientWrapper *jack_client_wrapper) {
    _jack_client_wrapper = jack_client_wrapper;

    if (!_jack_client_wrapper->create_port("master_out_1", OUTPUT_PORT)) {
        cerr << LOG_LABEL << "Failed to create JACK client master output 1 port" << endl;
        return false;
    }

    if (!_jack_client_wrapper->create_port("master_out_2", OUTPUT_PORT)) {
        cerr << LOG_LABEL << "Failed to create JACK client master output 2 port" << endl;
        return false;
    }

    _click.initialize(jack_client_wrapper);
    return true;
}

bool Engine::is_alive() {
    return _is_alive;
}

string Engine::get_engine_status() {
    return is_alive() ? "alive" : "dead";
}

int Engine::start() {
    cout << LOG_LABEL << " started..." << endl;

    _click.start();

    while(is_alive()){
        // do main loop stuff here

        cout << LOG_LABEL << "main loop - doing nothing..." << endl;
        // sleep for 5 seconds
        usleep(5000000);
    }

    return 0;
}
