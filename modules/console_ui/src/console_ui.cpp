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

#include <console_ui/console_ui.hpp>

#include <processing/types.hpp>

#include <iostream>

Console_ui::Console_ui::Console_ui(const int tempo)
    : _tempo{tempo}
{
}

void Console_ui::Console_ui::update(const int current_timeslot, const std::vector<Processing::Loop>& loops)
{
    print_timeline(current_timeslot, loops);
}

void Console_ui::Console_ui::print_timeline(const int current_timeslot, const std::vector<Processing::Loop>& loops)
{
    if (current_timeslot != _last_timeslot_printed) {
        system("clear");
        // std::cout << "\033[2J\033[0;0H";

        std::cout << "############" << "\n";
        std::cout << "  timeline  " << "\n";
        std::cout << "############" << "\n";

        std::cout << "\n";

        std::cout << "tempo: " << std::to_string(_tempo) << "\n";

        std::cout << "\n";

        std::cout << std::string(_displayed_timeslots * 2, '-') << "-" << "\n";

        for (int i = 0; i < _displayed_timeslots; i++) {
            if (i == current_timeslot) {
                std::cout << "|*";
            }
            else {
                std::cout << "| ";
            }
        }
        std::cout << "|" << "\n";

        std::cout << std::string(_displayed_timeslots * 2, '-') << "-" << "\n";

        for (auto& loop : loops) {
            for (int i = 0; i < _displayed_timeslots; i++) {
                if (i == loop.begin_timeslot) {
                    std::cout << "|:";
                }
                else if (i == loop.end_timeslot) {
                    std::cout << " :|";

                    if (loop.repeats != -1)
                        std::cout << std::to_string(loop.repeats) << "x";
                }
                else {
                    std::cout << "  ";
                }
            }
            std::cout << "\n";
        }

        _last_timeslot_printed = current_timeslot;
    }
}
