cmake_minimum_required(VERSION 3.17)

project(Beetchef VERSION 1.0.0)

#add_compile_options(-W -Wall -Werror)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/archive")

add_executable(
    beetchef

    src/beetchef.cpp
    src/click.cpp
    src/console_ui.cpp
    src/engine.cpp
    src/timeline.cpp
    src/track.cpp
)

set_target_properties(
    beetchef PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(beetchef PRIVATE src)

add_subdirectory(src/audio_base)
add_subdirectory(src/jack_audio_base)

target_link_libraries(beetchef PRIVATE audio_base)
target_link_libraries(beetchef PRIVATE jack_audio_base)
