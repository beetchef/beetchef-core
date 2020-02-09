#ifndef BEETCHEF_ENGINE_HPP
#define BEETCHEF_ENGINE_HPP

#include "audio/audio_base.hpp"
#include "click.hpp"
#include "timeline.hpp"

#include <memory>
#include <string>

class Engine {
    public:
        Engine(Audio_base);
        int start();
        bool is_alive();
    private:
        std::string get_engine_status();

        static constexpr std::string_view log_label{"[engine]: "};
        Audio_base _audio_base;
        Click _click;
        bool _is_alive;
        Timeline _timeline{60, 4, 4, 44100, 1};
};

#endif // BEETCHEF_ENGINE_HPP
