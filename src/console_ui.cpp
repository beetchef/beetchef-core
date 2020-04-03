#include "console_ui.hpp"

#include "processing/types.hpp"

#include <iostream>

Console_ui::Console_ui(const int tempo)
    : _tempo{tempo}
{
}

void
Console_ui::update(const int current_timeslot, const std::vector<Loop>& loops)
{
    print_timeline(current_timeslot, loops);
}

void
Console_ui::print_timeline(const int current_timeslot, const std::vector<Loop>& loops)
{
    if (current_timeslot != _last_timeslot_printed) {
        system("clear");
        // std::cout << "\033[2J\033[0;0H";

        std::cout << "############" << std::endl;
        std::cout << "  timeline  " << std::endl;
        std::cout << "############" << std::endl;

        std::cout << std::endl;

        std::cout << "tempo: " << std::to_string(_tempo) << std::endl;

        std::cout << std::endl;

        std::cout << std::string(_displayed_timeslots * 2, '-') << "-" << std::endl;

        for (int i = 0; i < _displayed_timeslots; i++) {
            if (i == current_timeslot) {
                std::cout << "|*";
            }
            else {
                std::cout << "| ";
            }
        }
        std::cout << "|" << std::endl;

        std::cout << std::string(_displayed_timeslots * 2, '-') << "-" << std::endl;

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
            std::cout << std::endl;
        }

        _last_timeslot_printed = current_timeslot;
    }
}
