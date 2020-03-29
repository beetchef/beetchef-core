#ifndef BEETCHEF_TIMELINE_HPP
#define BEETCHEF_TIMELINE_HPP

#include "audio_base/types.hpp"

#include <string>
#include <vector>

struct Loop {
    int begin_timeslot{0};
    int end_timeslot{0};
    int repeats{-1};
};

struct Process_frame {
    int begin_timeslot{0};
    nframes_t offset{0};
    nframes_t nframes{0};
};

class Timeline {
    public:

        Timeline(
            int tempo = 60,
            int signature_numerator = 4,
            int signature_denominator = 4,
            nframes_t sample_rate = 44100,
            int timeslots_per_beat = 1);

            int get_current_timeslot() const;
            const std::vector<Loop>& get_loops() const;
            const std::vector<Process_frame>& get_process_queue() const;

            void update(nframes_t);
    private:
        static constexpr std::string_view log_label{"[timeline]: "};

        struct Click_info {
            int tempo;
            int signature_numerator;
            int signature_denominator;
            nframes_t sample_rate;

            nframes_t get_beat_length() const;
        };

        Click_info _click_info;

        std::vector<Loop> _loops;

        int _timeslots_per_beat;
        nframes_t _timeslot_length;

        int _current_timeslot{0};
        nframes_t _current_offset{0};

        std::vector<Process_frame> _process_queue;
};

#endif // BEETCHEF_TIMELINE_HPP
