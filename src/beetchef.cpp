#include <iostream>
#include "engine.hpp"
using namespace std;


int main(int argc, char** argv) {
    Engine *engine = new Engine();
    engine->startEngine();
    cout << engine->isAlive();
    return 0;
}