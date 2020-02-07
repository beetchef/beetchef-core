#ifndef BEETCHEF_TIMELINE_HPP
#define BEETCHEF_TIMELINE_HPP

#include "audio/audio_types.hpp"

#include <string>

class Timeline {
    public:
        Timeline(
            int tempo,
            int signature_numerator,
            int signature_denominator,
            nframes_t sample_rate,
            int timeslots_per_beat);

    private:
        static constexpr std::string_view log_label{"[timeline]: "};
        struct Click_info {
            Click_info(
                int tempo = 60,
                int signature_numerator = 4,
                int signature_denominator = 4,
                nframes_t sample_rate = 44100);

            int _tempo;
            int _signature_numerator;
            int _signature_denominator;
            nframes_t _sample_rate;
            nframes_t _beat_length;
        };

        Click_info _click_info;
        int _timeslots_per_beat{1};
        nframes_t _timeslot_length{0};
        int _current_timeslot{0};
};

#endif // BEETCHEF_TIMELINE_HPP
