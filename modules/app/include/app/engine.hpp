#ifndef BEETCHEF_ENGINE_HPP
#define BEETCHEF_ENGINE_HPP

#include <console_ui/console_ui.hpp>

#include <audio/audio_interface_wrap.hpp>

#include <processing/timeline.hpp>
#include <processing/track.hpp>

#include <memory>
#include <string>
#include <vector>

namespace Beetchef
{
    class Engine {
        public:

            template<typename T>
            explicit Engine(T audio_interface)
                : _audio_interface{std::move(audio_interface)}
                , _timeline{120, 4, 4, _audio_interface.get_sample_rate(), 1}
                , _console_ui{120}
                , _running{false}
            {
                init();
            }

            void start();
            void stop();

            bool is_running();

        private:
            static constexpr std::string_view log_label{"[engine]"};

            Audio::Audio_interface_wrap _audio_interface;
            Processing::Timeline _timeline;
            Console_ui::Console_ui _console_ui;
            bool _running;

            std::vector<Processing::Track> _tracks;

            void init();
    };

}; // namespace Beetchef

#endif // BEETCHEF_ENGINE_HPP
