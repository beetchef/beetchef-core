/*
 *  Beetchef - real time audio sequencer
 *  Copyright (C) 2020 Anton Šefčík
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
