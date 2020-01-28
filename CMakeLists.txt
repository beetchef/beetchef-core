cmake_minimum_required(VERSION 3.10.2)

# project name
project(Beetchef VERSION 1.0.0)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)

# set compiler flags
set(CMAKE_CXX_FLAGS "-pthread -ljack -lpthread")

# set output directory for final executable to be ./build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

# add external library cmake project
add_subdirectory(lib/oscpack_1_1_0)

# include src as project root
include_directories(${CMAKE_SOURCE_DIR}/src)

# include external library sources
target_include_directories(oscpack PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib/oscpack_1_1_0")

# add "make run" target
add_custom_target(run
    COMMAND build/bin/beetchef
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# set beetchef sources to variable SOURCES
file(GLOB SOURCES "./src/*.cpp" "./src/*.hpp" "./src/**/*.cpp" "./src/**/*.hpp" "./src/**/**/*.cpp" "./src/**/**/*.hpp") # TODO: use target_sources,

# specify final executable beetchef based on sources specified in variable SOURCES
add_executable(beetchef ${SOURCES})

# link the executable and the library together
target_link_libraries(beetchef oscpack)
