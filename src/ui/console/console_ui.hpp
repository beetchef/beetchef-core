#ifndef BEETCHEF_CONSOLE_UI_HPP
#define BEETCHEF_CONSOLE_UI_HPP

#include "timeline.hpp"

#include <vector>

class Console_ui {
    public:
        void update(const int current_timeslot, const std::vector<Timeline::Loop>&);
    private:
        int _displayed_timeslots{20};
        int _last_timeslot_printed{-1};

        void print_timeline(const int current_timeslot, const std::vector<Timeline::Loop>&);
};

#endif // BEETCHEF_CONSOLE_UI_HPP
