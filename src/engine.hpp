#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "audio/audio_base.hpp"
#include "click.hpp"

#include <memory>
#include <string>

class Engine {
    public:
        Engine(Audio_base);
        int start();
        bool is_alive();
    private:
        static constexpr std::string_view log_label{"[engine]: "};
        Audio_base _audio_base;
        Click _click;
        bool _is_alive;
        std::string get_engine_status();
};

#endif // ENGINE_HPP
