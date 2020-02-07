#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "audio/audio_types.hpp"

#include <string>

class Timeline {
    public:
        Timeline(
            unsigned short int tempo,
            unsigned short int signature_numerator,
            unsigned short int signature_denominator,
            nframes_t sample_rate,
            unsigned short int timeslots_per_beat);

    private:
        static constexpr std::string_view log_label{"[timeline]: "};
        struct Click_info {
            Click_info(
                unsigned short int tempo,
                unsigned short int signature_numerator,
                unsigned short int signature_denominator,
                nframes_t sample_rate);

            unsigned short int _tempo{60};
            unsigned short int _signature_numerator{4};
            unsigned short int _signature_denominator{4};
            nframes_t _sample_rate{0};
            nframes_t _beat_length{0};
        };

        Click_info _click_info;
        unsigned short int _timeslots_per_beat{1};
        nframes_t _timeslot_length{0};
        unsigned short int _current_timeslot{0};
};

#endif // TIMELINE_HPP
