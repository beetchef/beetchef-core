#include <string>
#include "click.hpp"
#include "jack_client_wrapper.hpp"

using std::string;

#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine {
    public:
        Engine();
        bool initialize(JackClientWrapper *jackClientWrapper);
        int start();
        bool isAlive();
    private:
        bool mAlive;
        JackClientWrapper *mJackClientWrapper;
        Click mClick;
        string getEngineStatus();
};

#endif
