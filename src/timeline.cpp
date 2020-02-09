#include "timeline.hpp"

#include <iostream>

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

    std::cout << log_label << "Created..." << std::endl;
    std::cout << log_label << "Tempo: " << _click_info.tempo << std::endl;
    std::cout << log_label << "Time signature: "
        << _click_info.signature_numerator << "/" << _click_info.signature_denominator << std::endl;
    std::cout << log_label << "Beat length: " << _click_info.get_beat_length() << std::endl;
    std::cout << log_label << "Timeslot length: " << _timeslot_length << std::endl;
}

void Timeline::process(nframes_t nframes)
{
    std::cout << log_label << "Processing " << std::to_string(nframes) << " frames..." << std::endl;
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
nframes_t Timeline::Click_info::get_beat_length()
{
    return 60 /* 1 minute in seconds */ / tempo * 4 /* quarter note length */ / signature_denominator * sample_rate;
}