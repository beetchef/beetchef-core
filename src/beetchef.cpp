#include <iostream>
#include "engine.hpp"

using std::cout;
using std::endl;


int main(int argc, char** argv) {
    
    Engine *engine = new Engine();
    engine->startEngine();
    cout << engine->isAlive();
    return 0;
}
