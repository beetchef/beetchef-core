#include "engine.hpp"
#include "click.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using std::cerr;
using std::cout;
using std::endl;

#define LOG_LABEL "[Engine]: "

Engine::Engine() : mClick(60, 4, 4) {
    mAlive = true;
    cout << LOG_LABEL << "created..." << endl;
}

bool Engine::initialize(JackClientWrapper *jackClientWrapper) {
    mJackClientWrapper = jackClientWrapper;

    if (!mJackClientWrapper->createPort("master_out_1", outputPort)) {
        cerr << LOG_LABEL << "Failed to create JACK client master output 1 port" << endl;
        return false;
    }

    if (!mJackClientWrapper->createPort("master_out_2", outputPort)) {
        cerr << LOG_LABEL << "Failed to create JACK client master output 2 port" << endl;
        return false;
    }

    mClick.initialize(jackClientWrapper);
    return true;
}

bool Engine::isAlive() {
    return mAlive;
}

string Engine::getEngineStatus() {
    return isAlive() ? "alive" : "dead";
}

int Engine::start() {
    cout << LOG_LABEL << " started..." << endl;

    mClick.start();

    while(isAlive()){
        // do main loop stuff here

        cout << LOG_LABEL << "main loop - doing nothing..." << endl;
        // sleep for 5 seconds
        usleep(5000000);
    }

    return 0;
}
