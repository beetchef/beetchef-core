#ifndef CLICK_HPP
#define CLICK_HPP

#include "messaging_handler.hpp"

#include <string>

class Click {
    public:
        Click();
        void start();
    protected:
    private:
        static constexpr std::string_view log_label{"[click]: "};
        unsigned int _tempo{60};
        unsigned int _signature_numerator{4};
        unsigned int _signature_denominator{4};
        unsigned int _current_beat{1};
        long _beat_duration;
        long _bar_duration;
        bool _is_running {false};
        Messaging_handler _messaging_handler;
};

#endif // CLICK_HPP
