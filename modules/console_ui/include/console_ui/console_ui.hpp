#ifndef BEETCHEF_CONSOLE_UI_HPP
#define BEETCHEF_CONSOLE_UI_HPP

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
