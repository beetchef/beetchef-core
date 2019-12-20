#include <iostream>
#include "engine.hpp"
#include "jack_client_wrapper.hpp"

using std::cerr;
using std::cout;
using std::endl;

#define LOG_LABEL "[beetchef]: "

int main(int argc, char** argv) {

    (void) argc; // suppress unused parameter warnings
    (void) argv; // suppress unused parameter warnings

    Jack_client_wrapper *jack_client_wrapper = new Jack_client_wrapper();

    Engine *engine = new Engine();

    if (!engine->initialize(jack_client_wrapper)) {
        cerr << LOG_LABEL << "Failed to initialize engine." << endl;
        exit(1);
    }

    if (!jack_client_wrapper->activate()) {
        cerr << LOG_LABEL << "Failed to activate JACK client." << endl;
        exit(1);
    }

    jack_client_wrapper->test_connect();

    engine->start();

    jack_client_wrapper->deactivate();

    delete engine;

    delete jack_client_wrapper;

    return 0;
}
