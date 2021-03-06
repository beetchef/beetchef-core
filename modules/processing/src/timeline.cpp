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

#include <processing/timeline.hpp>
#include <processing/types.hpp>

#include <vector>

#include <spdlog/spdlog.h>

using Processing::Timeline;

Timeline::Timeline(
    int tempo,
    int signature_numerator,
    int signature_denominator,
    Audio::nframes_t sample_rate,
    int timeslots_per_beat)
        : _click_config{tempo, signature_numerator, signature_denominator, sample_rate}
        , _timeslots_per_beat{timeslots_per_beat}
{
    _timeslot_length = _click_config.get_beat_length() / _timeslots_per_beat;

    _process_queue.reserve(2);

    // TMP
    //_loops.emplace_back(Loop{4, 7, 4});

    spdlog::info("{} Created.", log_label);
    spdlog::info("{} Tempo: {}", log_label, _click_config.tempo);
    spdlog::info("{} Time signature: {}/{}", log_label, _click_config.signature_numerator, _click_config.signature_denominator);
    spdlog::info("{} Beat length: {}", log_label, _click_config.get_beat_length());
    spdlog::info("{} Timeslot length: {}", log_label, _timeslot_length);
}

int Timeline::get_current_timeslot() const
{
    return _current_timeslot;
}

Audio::nframes_t Timeline::get_current_offset() const
{
    return _current_offset;
}

const std::vector<Processing::Loop>& Timeline::get_loops() const
{
    return _loops;
}

const std::vector<Processing::Process_frame>& Timeline::get_process_queue() const
{
    return _process_queue;
}

Timeline::Click_config Timeline::get_click_config() const
{
    return _click_config;
}

int Timeline::get_timeslots_per_beat() const
{
    return _timeslots_per_beat;
}

Audio::nframes_t Timeline::get_timeslot_length() const
{
    return _timeslot_length;
}

void Timeline::add_loop(Loop loop)
{
    _loops.emplace_back(loop);
}

void Timeline::update(const Audio::nframes_t nframes)
{
    update(nframes, true);
}

void Timeline::update(const Audio::nframes_t nframes, bool clear_queue)
{
    if (clear_queue)
    {
        _process_queue.clear();
    }

    int target_position = _current_offset + nframes;
    int exceeding_timeslots = target_position / _timeslot_length;

    if(exceeding_timeslots == 0) {
        // staying within current timeslot - the most frequent case
        _process_queue.emplace_back(Process_frame{_current_timeslot, _current_offset, nframes});
        _current_offset = target_position;
    }
    else if(_loops.empty() || _current_timeslot + exceeding_timeslots <= _loops.back().end_timeslot) {
        // exceeding current timeslot but staying within current loop - less frequent case
        _process_queue.emplace_back(Process_frame{_current_timeslot, _current_offset, nframes});
        _current_timeslot += exceeding_timeslots;
        _current_offset = target_position % _timeslot_length;
    }
    else {
        // exceeding current timeslot and current loop - the least frequent case

        // rest of current loop
        Audio::nframes_t loop_frames_left = (_loops.back().end_timeslot + 1 - _current_timeslot) * _timeslot_length - _current_offset;
        _process_queue.emplace_back(Process_frame{_current_timeslot, _current_offset, loop_frames_left});

        // set position according to loop
        _current_timeslot = _loops.back().begin_timeslot;
        _current_offset = 0;

        if (_loops.back().repeats == 2)
            _loops.pop_back();
        else if (_loops.back().repeats != -1)
            _loops.back().repeats--;

        update(nframes - loop_frames_left, false);
    }
}

/*
    NOTE:

    beat length (in nframes_t) is calculated as:

        beat_length = 60 seconds / tempo * quarter note length / signature_denominator * sample rate

    EXAMPLE:
    (1 beat each second)

    signature = 4/4
    signature_numerator = 4
    signature_denominator = 4
    tempo = 120 bpm (quarter note beats per minute)
    sample_rate = 44100 Hz

    beat_length = 60(1min in seconds) / 120(tempo) * 4(quarter note length) / 4(signature_denominator) * sample_rate = 60 / 120 * 44100 = 22050 frames
*/
Audio::nframes_t Timeline::Click_config::get_beat_length() const
{
    return 60.0f /* 1 minute in seconds */ / tempo * 4.0f /* quarter note length */ / signature_denominator * sample_rate;
}
