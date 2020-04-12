add_library(
    messaging STATIC

    src/messaging_handler.cpp
)

set_target_properties(
    messaging PROPERTIES
    
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(messaging PUBLIC include)
target_include_directories(messaging PRIVATE lib/oscpack_1_1_0)

add_subdirectory(lib/oscpack_1_1_0)

target_link_libraries(messaging PUBLIC oscpack)
target_link_libraries(messaging PRIVATE spdlog::spdlog)
