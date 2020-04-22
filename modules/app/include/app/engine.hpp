/*
 *  Beetchef - real time audio sequencer
 *  Copyright (C) 2020 Anton Šefčík
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
