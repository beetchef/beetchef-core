#include <string>

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
        string getEngineStatus();
};

#endif
