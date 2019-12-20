#include <string>
#include "click.hpp"
#include "jack_client_wrapper.hpp"

#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine {
    public:
        Engine();
        bool initialize(Jack_client_wrapper *jack_client_wrapper);
        int start();
        bool is_alive();
    private:
        bool _is_alive;
        Jack_client_wrapper *_jack_client_wrapper;
        Click _click;
        std::string get_engine_status();
};

#endif
