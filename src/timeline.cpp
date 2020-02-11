#include "timeline.hpp"

#include <iostream>
#include <vector>

Timeline::Timeline(
    int tempo,
    int signature_numerator,
    int signature_denominator,
    nframes_t sample_rate,
    int timeslots_per_beat)
        : _click_info{tempo, signature_numerator, signature_denominator, sample_rate}
        , _timeslots_per_beat{timeslots_per_beat}
{
    _timeslot_length = _click_info.get_beat_length() / _timeslots_per_beat;

    _process_queue.reserve(2);
    // TMP
    _loops.emplace_back(Loop{0, 3, 2});

    std::cout << log_label << "Created..." << std::endl;
    std::cout << log_label << "Tempo: " << _click_info.tempo << std::endl;
    std::cout << log_label << "Time signature: "
        << _click_info.signature_numerator << "/" << _click_info.signature_denominator << std::endl;
    std::cout << log_label << "Beat length: " << _click_info.get_beat_length() << std::endl;
    std::cout << log_label << "Timeslot length: " << _timeslot_length << std::endl;
}

int
Timeline::process(const nframes_t nframes)
{
    prepare_process_queue(nframes);
    // TODO: process the queue here...
    std::cout << log_label << "Processing frame " << std::to_string(_process_queue.back().begin_timeslot) << std::endl;
    _process_queue.clear();

    return 0;
}

void
Timeline::prepare_process_queue(const nframes_t nframes)
{
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
        nframes_t loop_frames_left = (_loops.back().end_timeslot + 1 - _current_timeslot) * _timeslot_length - _current_offset;
        _process_queue.emplace_back(Process_frame{_current_timeslot, _current_offset, loop_frames_left});

        // set position according to loop
        _current_timeslot = _loops.back().begin_timeslot;
        _current_offset = 0;

        prepare_process_queue(nframes - loop_frames_left);
    }
}

/*
    NOTE:

    beat length (in nframes_t) is calculated as:

        beat_duration = 1 minute / tempo * quarter note length / signature_denominator * sample rate

    EXAMPLE:
    (1 beat each second)

    signature = 4/4
    signature_numerator = 4
    signature_denominator = 4
    tempo = 120 bpm (quarter note beats per minute)
    sample_rate = 44100 Hz

    beat_duration = 60(1min in seconds) / 120(tempo) * 4(quarter note length) / 4(signature_denominator) * sample_rate = 60 / 120 * 44100 = 22050 frames
*/
nframes_t
Timeline::Click_info::get_beat_length()
{
    return 60 /* 1 minute in seconds */ / tempo * 4 /* quarter note length */ / signature_denominator * sample_rate;
}
