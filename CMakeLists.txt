cmake_minimum_required(VERSION 3.17)

project(Beetchef VERSION 1.0.0)

add_compile_options(-W -Wall -Werror)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/archive")

find_package(spdlog REQUIRED)

enable_testing()

add_subdirectory(modules/audio)
add_subdirectory(modules/jack_audio)
add_subdirectory(modules/processing)
add_subdirectory(modules/console_ui)
add_subdirectory(modules/app)
