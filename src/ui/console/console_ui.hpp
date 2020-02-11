#ifndef BEETCHEF_CONSOLE_UI_HPP
#define BEETCHEF_CONSOLE_UI_HPP

#include "timeline.hpp"

#include <vector>

class Console_ui {
    public:
        void update(int current_timeslot, std::vector<Timeline::Loop>);
    private:
        int _displayed_timeslots{12};
        int _last_timeslot_printed{-1};

        void print_timeline(int current_timeslot, std::vector<Timeline::Loop>);
};

#endif // BEETCHEF_CONSOLE_UI_HPP
