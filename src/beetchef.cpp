#include <iostream>
#include "engine.hpp"

using std::cout;
using std::endl;


int main(int argc, char** argv) {

    (void) argc; // suppress unused parameter warnings
    (void) argv; // suppress unused parameter warnings

    Engine *engine = new Engine();
    engine->startEngine();
    cout << engine->isAlive();
    return 0;
}
