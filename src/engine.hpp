#ifndef BEETCHEF_ENGINE_HPP
#define BEETCHEF_ENGINE_HPP

#include "click.hpp"
#include "timeline.hpp"

#include "audio/audio_base.hpp"

#include "ui/console/console_ui.hpp"

#include <memory>
#include <string>

class Engine {
    public:
        explicit Engine(Audio_base);
        int start();
        bool is_alive();
    private:
        std::string get_engine_status();

        static constexpr std::string_view log_label{"[engine]: "};
        Audio_base _audio_base;
        Click _click;
        bool _is_alive;
        Timeline _timeline;
        Console_ui _console_ui;
};

#endif // BEETCHEF_ENGINE_HPP
