#ifndef BEETCHEF_PROCESSING_TYPES_HPP
#define BEETCHEF_PROCESSING_TYPES_HPP

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

}; // namespace Processing

#endif // BEETCHEF_PROCESSING_TYPES_HPP