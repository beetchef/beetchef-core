#include "engine.hpp"

#include "jack_audio/jack_audio_interface.hpp"
#include "jack_audio/jack_client.hpp"

#include <spdlog/spdlog.h>

#include <exception>
#include <memory>
#include <stdexcept>
#include <string>


namespace Beetchef {
    static constexpr std::string_view log_label{"[beetchef]"};
    void print_current_exception_with_nested(int level = 0)
    {
        try {
            // re-throw current exception
            throw;
        }
        catch (const std::exception& err) {
            // it's std::exception, print it
            spdlog::error("\t{}exception: {}", std::string(level, ' '), err.what());
        }
        catch (...) {
            // it's an unknown exception, print message
            spdlog::error("\t{}unknown exception", std::string(level, ' '));
        }

        try {
            // re-throw current exception
            throw;
        }
        catch (const std::nested_exception& nested) {
            // it's std::nested_exception (meaning it in fact contains a nested exception)
            try {
                // re-throw nested exception
                nested.rethrow_nested();
            }
            catch (...) {
                // catch it and print it with its nested exceptions, if any
                print_current_exception_with_nested(level + 1); // recursion
            }
        }
        catch (...) {
            // it's not std::nested_exception - do nothing - end recursion
        }
    }
    static void exit_with_error(std::string msg)
    {
        spdlog::error("{} {}", log_label, msg);
        print_current_exception_with_nested();
        spdlog::error("{} Exiting.", log_label);
        exit(1);
    }
}

int main()
try {

    Jack_audio::Jack_client jack_client;
    Jack_audio::Jack_audio_interface jack_audio_interface(std::move(jack_client));
    Beetchef::Engine engine(std::move(jack_audio_interface));

    engine.start();

    return 0;
}
catch (const std::runtime_error& err) {
    Beetchef::exit_with_error("Runtime error occurred:");
}
catch (const std::exception& err) {
    Beetchef::exit_with_error("Error occurred:");
}
catch (...) {
    Beetchef::exit_with_error("Unknown error occurred.");
}
