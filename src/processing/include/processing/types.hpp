#ifndef BEETCHEF_PROCESSING_TYPES_HPP
#define BEETCHEF_PROCESSING_TYPES_HPP

#include <audio/types.hpp>

namespace Processing
{
    struct Loop {
        int begin_timeslot{0};
        int end_timeslot{0};
        int repeats{-1};
    };

    struct Process_frame {
        int begin_timeslot{0};
        Audio::nframes_t offset{0};
        Audio::nframes_t nframes{0};
    };

}; //namespace Processing

#endif //BEETCHEF_PROCESSING_TYPES_HPP