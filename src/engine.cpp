#include "click.hpp"
#include "engine.hpp"

#include "processing/track.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>


void Engine::init()
{
    std::cout << log_label << "Created..." << std::endl;

    _tracks.emplace_back(&_audio_interface, std::vector<int>{0, 1}, "track-1");

    _audio_interface.register_process_callback([&](nframes_t nframes)->int{
        _timeline.update(nframes);
        //_console_ui.update(_timeline.get_current_timeslot(), _timeline.get_loops());

        for (auto& track : _tracks) {
            for (auto& process_frame : _timeline.get_process_queue()) {
                for (int chan_idx = 0; chan_idx < _audio_interface.get_out_chan_count(); chan_idx++) {
                    track.produce_to(chan_idx, process_frame, _audio_interface.get_out_buf(chan_idx, process_frame.nframes));
                }
            }
        }

        return 0;
    });

    std::cout << log_label << "Timeline registered for processing..." << std::endl;

    _audio_interface.start_processing();

    std::cout << log_label << "Processing started..." << std::endl;
}

bool Engine::is_alive()
{
    return _is_alive;
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
