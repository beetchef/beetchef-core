#include "audio/audio_base.hpp"
#include "audio/audio_interface.hpp"
#include "jack_audio/jack_audio_interface.hpp"
#include "jack_audio/jack_client.hpp"
#include "click.hpp"
#include "engine.hpp"

#include "processing/track.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>

Engine::Engine(Audio_base audio_base)
    : _audio_base{std::move(audio_base)}
    , _timeline{120, 4, 4, _audio_base.get_audio_interface()->get_sample_rate(), 1}
    , _console_ui{120}
    , _click{} // TODO: _click will be removed from here
    , _is_alive{true}
{
    std::cout << log_label << "Created..." << std::endl;

    _tracks.emplace_back(_audio_base.get_audio_interface(), std::vector<int>{0, 1}, "track-1");

    _audio_base.get_audio_interface()->register_process_callback([&](nframes_t nframes)->int{
        _timeline.update(nframes);
        //_console_ui.update(_timeline.get_current_timeslot(), _timeline.get_loops());

        for (auto& track : _tracks) {
            for (auto& process_frame : _timeline.get_process_queue()) {
                for (int chan_idx = 0; chan_idx < _audio_base.get_audio_interface()->get_out_chan_count(); chan_idx++) {
                    track.produce_to(chan_idx, process_frame, _audio_base.get_audio_interface()->get_out_buf(chan_idx, process_frame.nframes));
                }
            }
        }

        return 0;
    });

    std::cout << log_label << "Timeline registered for processing..." << std::endl;
}

bool Engine::is_alive()
{
    return _is_alive;
}

std::string Engine::get_engine_status()
{
    return is_alive() ? "alive" : "dead";
}

int Engine::start()
{
    std::cout << log_label << "Started..." << std::endl;

    _click.start();

    while(is_alive()) {

        // do main loop stuff here

        // TESTING
        //_timeline.process(50000);
        //usleep(500000);

        //std::cout << log_label << "Main loop - doing nothing..." << std::endl;
        // sleep for 5 seconds
        usleep(5000000);
    }

    return 0;
}
