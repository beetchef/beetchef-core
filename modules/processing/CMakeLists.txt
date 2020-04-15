cmake_minimum_required(VERSION 3.17)

project(processing)

# sources

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

# tests

find_package(Catch2 REQUIRED)

enable_testing()

add_executable(
    processing_tests

    test/processing_tests.cpp
    test/timeline_tests.cpp
)

set_target_properties(
    processing_tests PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(processing_tests PRIVATE Catch2::Catch2 processing)

include(CTest)
include(Catch)
catch_discover_tests(processing_tests)
