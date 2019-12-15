#include <string>
#include "click.hpp"
#include "jack_client_wrapper.hpp"

using std::string;

#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine {
    public:
        Engine();
        bool initialize(JackClientWrapper *jack_client_wrapper);
        int start();
        bool is_alive();
    private:
        bool _is_alive;
        JackClientWrapper *_jack_client_wrapper;
        Click _click;
        string get_engine_status();
};

#endif
