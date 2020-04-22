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

#ifndef BEETCHEF_CLICK_HPP
#define BEETCHEF_CLICK_HPP

//#include <messaging/messaging_handler.hpp>

#include <string>

namespace Console_ui
{
    class Click {
        public:
            Click();
            void start();
        protected:
        private:
            static constexpr std::string_view log_label{"[click]"};
            unsigned int _tempo{60};
            unsigned int _signature_numerator{4};
            unsigned int _signature_denominator{4};
            unsigned int _current_beat{1};
            long _beat_duration;
            long _bar_duration;
            bool _is_running {false};
            //Messaging_handler _messaging_handler;
    };

}; // namespace Console_ui

#endif // BEETCHEF_CLICK_HPP
