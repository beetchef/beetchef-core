#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "audio/audio_provider.hpp"
#include "click.hpp"

#include <memory>
#include <string>

class Engine {
    public:
        Engine(std::unique_ptr<Audio_provider>);
        int start();
        bool is_alive();
    private:
        static constexpr std::string_view log_label{"[engine]: "};
        std::unique_ptr<Audio_provider> _audio_provider;
        Click _click;
        bool _is_alive;
        std::string get_engine_status();
};

#endif // ENGINE_HPP
