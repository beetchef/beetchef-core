#ifndef BEETCHEF_ENGINE_HPP
#define BEETCHEF_ENGINE_HPP

#include "click.hpp"
#include "console_ui.hpp"

#include "audio/audio_interface_wrap.hpp"

#include "processing/timeline.hpp"
#include "processing/track.hpp"

#include <memory>
#include <string>
#include <vector>

class Engine {
    public:

        template<typename T>
        explicit Engine(T audio_interface)
            : _audio_interface{std::move(audio_interface)}
            , _timeline{120, 4, 4, _audio_interface.get_sample_rate(), 1}
            , _console_ui{120}
            , _click{} // TODO: _click will be removed from here
            , _is_alive{true}
        {
            init();
        }

        int start();
        bool is_alive();

    private:
        static constexpr std::string_view log_label{"[engine]: "};

        Audio_interface_wrap _audio_interface;

        Click _click;
        bool _is_alive;
        Timeline _timeline;
        Console_ui _console_ui;

        std::vector<Track> _tracks;

        void init();
};

#endif // BEETCHEF_ENGINE_HPP
