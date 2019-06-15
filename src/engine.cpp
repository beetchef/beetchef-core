#include "engine.h"
#include <iostream>
using namespace std;



// Engine::Engine() {
//     cout << "creating engine" << endl;
// }

bool Engine::isAlive() {
     cout << "creating engine" << endl;
    return _isAlive; 
}

int Engine::startEngine() {
    _isAlive=true;
    while(_isAlive){
        cout << "creating engine" << endl;
    }
    return 0;
}