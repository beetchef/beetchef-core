cmake_minimum_required(VERSION 3.17)

project(processing)

add_library(
    processing STATIC

    src/timeline.cpp
    src/track.cpp
)

set_target_properties(
    processing PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(processing PUBLIC include)

target_link_libraries(processing
    PUBLIC audio
    PRIVATE spdlog::spdlog
)
