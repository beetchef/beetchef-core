#ifndef BEETCHEF_CONSOLE_UI_HPP
#define BEETCHEF_CONSOLE_UI_HPP

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

#include <processing/types.hpp>

#include <vector>

namespace Console_ui
{
    class Console_ui {
        public:
            Console_ui(const int tempo = 60);
            void update(const int current_timeslot, const std::vector<Processing::Loop>&);
        private:
            int _displayed_timeslots{20};
            int _tempo;
            int _last_timeslot_printed{-1};

            void print_timeline(const int current_timeslot, const std::vector<Processing::Loop>&);
    };

}; // namespace Console_ui

#endif // BEETCHEF_CONSOLE_UI_HPP
