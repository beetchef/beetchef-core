add_library(
    audio_base STATIC

    src/audio_base.cpp
    src/audio_interface.cpp
    src/callback_function.cpp
)

target_include_directories(audio_base PUBLIC include)
target_include_directories(audio_base PRIVATE src)
