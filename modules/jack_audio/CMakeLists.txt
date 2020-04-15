cmake_minimum_required(VERSION 3.17)

project(jack_audio)

add_library(
    jack_audio STATIC

    src/jack_audio_interface.cpp
    src/jack_client.cpp
    src/jack_port.cpp
)

set_target_properties(
    jack_audio PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_options(jack_audio PUBLIC "-ljack")
target_link_options(jack_audio PUBLIC "-lpthread")

target_include_directories(jack_audio PUBLIC include)

target_link_libraries(jack_audio PRIVATE spdlog::spdlog)
