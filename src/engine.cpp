#include "engine.hpp"
#include <iostream>
#include <string>
using namespace std;



Engine::Engine() {
    cout << "creating engine..." << endl;
    _alive = true;
}

bool Engine::isAlive() {
    return _alive; 
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