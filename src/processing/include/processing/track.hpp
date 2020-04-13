#ifndef BEETCHEF_TRACK_HPP
#define BEETCHEF_TRACK_HPP

#include <audio/audio_interface_wrap.hpp>
#include <audio/types.hpp>

#include <processing/types.hpp>

#include <string>
#include <vector>

namespace Processing
{
    class Track {
        public:
            Track(const std::string name, const std::vector<int> in_chans, Audio::Audio_interface_wrap* const);

            void produce_to(const int chan_idx, const Process_frame& process_frame, Audio::sample_t* out_buf);

        private:
            std::string _name;
            std::vector<int> _in_chans;
            Audio::Audio_interface_wrap* _audio_interface;
    };

}; // namespace Processing

#endif // BEETCHEF_TRACK_HPP
