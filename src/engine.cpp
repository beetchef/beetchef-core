#include "engine.hpp"
#include "click.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using std::cout;
using std::endl;

const string LOG_LABEL = "[Engine]: ";

Engine::Engine() : mClick(60, 4, 4) {
    mAlive = true;
    cout << LOG_LABEL << "created..." << endl;
}

bool Engine::isAlive() {
    return mAlive;
}

string Engine::getEngineStatus() {
    return isAlive() ? "alive" : "dead";
}

int Engine::startEngine() {
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
