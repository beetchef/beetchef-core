#include "engine.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;


Engine::Engine() {
    cout << "creating engine..." << endl;
    mAlive = true;
}

bool Engine::isAlive() {
    return mAlive;
}

string Engine::getEngineStatus() {
    return isAlive() ? "alive" : "dead";
}

int Engine::startEngine() {
    while(isAlive()){
        cout << "engine status: " << getEngineStatus() << endl;
    }
    return 0;
}
