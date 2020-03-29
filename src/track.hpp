#ifndef BEETCHEF_TRACK_HPP
#define BEETCHEF_TRACK_HPP

#include "timeline.hpp"

#include "audio_base/audio_interface.hpp"
#include "audio_base/types.hpp"

#include <string>
#include <vector>

class Track {
    public:
        Track(Audio_interface* const, const std::vector<int> in_chans, const std::string name);

        void produce_to(const int chan_idx, const Process_frame& process_frame, sample_t* out_buf);

    private:
        std::string _name;
        std::vector<int> _in_chans;
        Audio_interface* _audio_interface;
};

#endif // BEETCHEF_TRACK_HPP
