#include "engine.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace Beetchef {
    static constexpr std::string_view log_label{"[beetchef]: "};
}

int main(int argc, char** argv)
{

    (void) argc; // suppress unused parameter warnings
    (void) argv; // suppress unused parameter warnings

    Engine engine;

    if (!engine.init()) {
        std::cerr << Beetchef::log_label << "Failed to initialize engine." << std::endl;
        exit(1);
    }

    engine.start();

    return 0;
}
