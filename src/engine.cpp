#include "audio/audio_base.hpp"
#include "audio/audio_interface.hpp"
#include "audio/jack/jack_audio_interface.hpp"
#include "audio/jack/jack_client.hpp"
#include "beetchef_error.hpp"
#include "click.hpp"
#include "engine.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>

Engine::Engine(Audio_base audio_base)
try
    : _audio_base{std::move(audio_base)}
    , _click{} // TODO: _click will be removed from here
    , _is_alive{true}
{
    std::cout << log_label << "Created..." << std::endl;

    _audio_base.get_audio_interface()->register_process_callback([&](nframes_t nframes)->int{ return _timeline.process(nframes); });
    std::cout << log_label << "Timeline registered for processing..." << std::endl;
}
catch (...) {
    Beetchef_error err{"Failed to initialize engine."};
    std::throw_with_nested(err);
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

        std::cout << log_label << "Main loop - doing nothing..." << std::endl;
        // sleep for 5 seconds
        usleep(5000000);
    }

    return 0;
}
