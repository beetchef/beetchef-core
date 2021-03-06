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

#ifndef BEETCHEF_TIMELINE_HPP
#define BEETCHEF_TIMELINE_HPP

#include <audio/types.hpp>
#include <processing/types.hpp>

#include <string>
#include <vector>

namespace Processing
{
    class Timeline {
        public:

            Timeline(
                int tempo = 60,
                int signature_numerator = 4,
                int signature_denominator = 4,
                Audio::nframes_t sample_rate = 44100,
                int timeslots_per_beat = 1
            );

            struct Click_config {
                int tempo;
                int signature_numerator;
                int signature_denominator;
                Audio::nframes_t sample_rate;

                Audio::nframes_t get_beat_length() const;
            };

            int get_current_timeslot() const;
            Audio::nframes_t get_current_offset() const;
            const std::vector<Loop>& get_loops() const;
            const std::vector<Process_frame>& get_process_queue() const;

            Click_config get_click_config() const;
            int get_timeslots_per_beat() const;
            Audio::nframes_t get_timeslot_length() const;

            void add_loop(Loop);

            void update(Audio::nframes_t);

        private:
            static constexpr std::string_view log_label{"[timeline]"};

            Click_config _click_config;

            std::vector<Loop> _loops;

            int _timeslots_per_beat;
            Audio::nframes_t _timeslot_length;

            int _current_timeslot{0};
            Audio::nframes_t _current_offset{0};

            std::vector<Process_frame> _process_queue;

            void update(Audio::nframes_t, bool clear_queue);
    };
    
}; // namespace Processing

#endif // BEETCHEF_TIMELINE_HPP
