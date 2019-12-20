#include "engine.hpp"
#include "click.hpp"

#include <iostream>
#include <string>
#include <unistd.h>

#define LOG_LABEL "[Engine]: "

Engine::Engine() : _click(60, 4, 4) {
    _is_alive = true;
    std::cout << LOG_LABEL << "created..." << std::endl;
}

bool Engine::initialize(Jack_client_wrapper *jack_client_wrapper) {
    _jack_client_wrapper = jack_client_wrapper;

    if (!_jack_client_wrapper->create_port("master_out_1", OUTPUT_PORT)) {
        std::cerr << LOG_LABEL << "Failed to create JACK client master output 1 port" << std::endl;
        return false;
    }

    if (!_jack_client_wrapper->create_port("master_out_2", OUTPUT_PORT)) {
        std::cerr << LOG_LABEL << "Failed to create JACK client master output 2 port" << std::endl;
        return false;
    }

    _click.initialize(jack_client_wrapper);
    return true;
}

bool Engine::is_alive() {
    return _is_alive;
}

std::string Engine::get_engine_status() {
    return is_alive() ? "alive" : "dead";
}

int Engine::start() {
    std::cout << LOG_LABEL << " started..." << std::endl;

    _click.start();

    while(is_alive()){
        // do main loop stuff here

        std::cout << LOG_LABEL << "main loop - doing nothing..." << std::endl;
        // sleep for 5 seconds
        usleep(5000000);
    }

    return 0;
}
