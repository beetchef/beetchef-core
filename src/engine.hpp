#ifndef BEETCHEF_ENGINE_HPP
#define BEETCHEF_ENGINE_HPP

#include "click.hpp"
#include "console_ui.hpp"

#include "audio/audio_base.hpp"

#include "processing/timeline.hpp"
#include "processing/track.hpp"

#include <memory>
#include <string>
#include <vector>

class Engine {
    public:
        explicit Engine(Audio_base);
        int start();
        bool is_alive();
    private:
        static constexpr std::string_view log_label{"[engine]: "};
        Audio_base _audio_base;
        Click _click;
        bool _is_alive;
        Timeline _timeline;
        Console_ui _console_ui;

        std::vector<Track> _tracks;

        std::string get_engine_status();
};

#endif // BEETCHEF_ENGINE_HPP
