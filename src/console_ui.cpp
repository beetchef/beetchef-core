#include "console_ui.hpp"

#include "processing/types.hpp"

#include <iostream>

using Beetchef::Console_ui;

Console_ui::Console_ui(const int tempo)
    : _tempo{tempo}
{
}

void
Console_ui::update(const int current_timeslot, const std::vector<Processing::Loop>& loops)
{
    print_timeline(current_timeslot, loops);
}

void
Console_ui::print_timeline(const int current_timeslot, const std::vector<Processing::Loop>& loops)
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
