#ifndef BEETCHEF_PROCESSING_TYPES_HPP
#define BEETCHEF_PROCESSING_TYPES_HPP

#include "audio_base/types.hpp"

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

#endif //BEETCHEF_PROCESSING_TYPES_HPP