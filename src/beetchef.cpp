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

    JackClientWrapper *jackClientWrapper = new JackClientWrapper();

    Engine *engine = new Engine();

    if (!engine->initialize(jackClientWrapper)) {
        cerr << LOG_LABEL << "Failed to initialize engine." << endl;
        exit(1);
    }

    if (!jackClientWrapper->activate()) {
        cerr << LOG_LABEL << "Failed to activate JACK client." << endl;
        exit(1);
    }

    jackClientWrapper->testConnect();

    engine->start();

    jackClientWrapper->deactivate();

    delete engine;

    delete jackClientWrapper;

    return 0;
}
