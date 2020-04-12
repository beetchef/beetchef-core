add_library(
    audio STATIC

    src/audio_interface_wrap.cpp
    src/callback_function.cpp
)

set_target_properties(
    audio PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(audio PUBLIC include)
