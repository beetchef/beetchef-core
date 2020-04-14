cmake_minimum_required(VERSION 3.17)

project(app)

# sources

add_library(engine STATIC src/engine.cpp)

set_target_properties(
    engine PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(engine PUBLIC include)

target_link_libraries(engine
    PUBLIC audio processing console_ui
    PRIVATE spdlog::spdlog
)

add_executable(app src/beetchef.cpp)

set_target_properties(
    app PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(app PRIVATE engine jack_audio spdlog::spdlog)

# tests

find_package(Catch2 REQUIRED)

add_executable(app_tests test/app_tests.cpp)

set_target_properties(
    app_tests PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(app_tests PRIVATE Catch2::Catch2 engine)

include(CTest)
include(Catch)
catch_discover_tests(app_tests)
