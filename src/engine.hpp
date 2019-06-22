#include <string>
#include "click.hpp"

using std::string;

#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine {
    public:
        Engine();
        int startEngine();
        bool isAlive();
    private:
        bool mAlive;
        Click mClick;
        string getEngineStatus();
};

#endif
