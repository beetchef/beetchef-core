cmake_minimum_required(VERSION 3.17)

project(console_ui)

add_library(
    console_ui STATIC

    src/click.cpp
    src/console_ui.cpp
)

set_target_properties(
    console_ui PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(console_ui
    PUBLIC include
    PRIVATE src
)

target_link_libraries(console_ui PRIVATE processing spdlog::spdlog)
