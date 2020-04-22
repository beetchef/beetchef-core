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

#include <app/engine.hpp>

#include <processing/track.hpp>

#include <exception>
#include <memory>
#include <string>
#include <unistd.h>

#include <spdlog/spdlog.h>

using Beetchef::Engine;

void Engine::init()
{
    spdlog::info("{} Created.", log_label);

    _tracks.emplace_back("track-1", std::vector<int>{0, 1}, &_audio_interface);

    _audio_interface.register_process_callback([&](Audio::nframes_t nframes)->int{
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

    spdlog::info("{} Timeline registered for processing.", log_label);

    _audio_interface.start_processing();

    spdlog::info("{} Processing started.", log_label);
}

void Engine::start()
{
    _running = true;

    spdlog::info("{} Started.", log_label);
    
    while(_running) {

        // do main loop stuff here

        // TESTING
        //_timeline.process(50000);
        //usleep(500000);

        //std::cout << log_label << "Main loop - doing nothing." << "\n";
        // sleep for 1 second
        sleep(1);
    }
}

void Engine::stop()
{
    _running = false;

    spdlog::info("{} Stopped.", log_label);
}

bool Engine::is_running()
{
    return _running;
}
