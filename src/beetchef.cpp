#include "engine.hpp"

#include "audio/audio_provider.hpp"
#include "audio/jack/jack_audio_provider.hpp"
#include "audio/jack/jack_client_wrapper.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>



namespace Beetchef {
    static constexpr std::string_view log_label{"[beetchef]: "};
    void print_current_exception_with_nested(int level =  0)
    {
        try {
            // re-throw current exception
            throw;
        }
        catch (const std::exception& err) {
            // it's std::exception, print it
            std::cerr << std::string(level, ' ') << "exception: " << err.what() << std::endl;
        }
        catch (...) {
            // it's an unknown exception, print message
            std::cerr << std::string(level, ' ') << "unknown exception" << std::endl;
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
        std::cerr << log_label << msg << std::endl;
        print_current_exception_with_nested();
        std::cerr << log_label << "Exiting..." << std::endl;
        exit(1);
    }
}

int main(int argc, char** argv)
try {

    (void) argc; // suppress unused parameter warnings
    (void) argv; // suppress unused parameter warnings

    Engine engine(std::make_unique<Jack_audio_provider>(std::move(std::make_unique<Jack_client_wrapper>())));

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
