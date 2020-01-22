#include "engine.hpp"
#include "beetchef_error.hpp"
#include "click.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>

Engine::Engine()
try
    :_jack_client{std::make_unique<Jack_client_wrapper>()},
    _click{*_jack_client.get()},
    _is_alive{true}
{
    std::cout << log_label << "Created..." << std::endl;
}
catch (...) {
    Beetchef_error err{"Failed to initialize engine."};
    std::throw_with_nested(err);
}

bool Engine::init()
{
    /*if (!_jack_client->register_port("master_out_1", PortType::output)) {
        std::cerr << log_label << "Failed to register JACK client master output 1 port" << std::endl;
        return false;
    }

    if (!_jack_client->register_port("master_out_2", PortType::output)) {
        std::cerr << log_label << "Failed to register JACK client master output 2 port" << std::endl;
        return false;
    }
*/
    _click.init();
    return true;
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
