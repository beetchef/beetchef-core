#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "click.hpp"
#include "jack_client_wrapper.hpp"

#include <memory>
#include <string>

class Engine {
    public:
        Engine();
        bool init();
        int start();
        bool is_alive();
    private:
        static constexpr std::string_view log_label{"[engine]: "};
        std::unique_ptr<Jack_client_wrapper> _jack_client;
        Click _click;
        bool _is_alive;
        std::string get_engine_status();
};

#endif // ENGINE_HPP
