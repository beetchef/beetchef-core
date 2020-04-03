add_library(
    audio STATIC

    src/audio_base.cpp
    src/audio_interface.cpp
    src/callback_function.cpp
)

target_include_directories(audio PUBLIC include)
target_include_directories(audio PRIVATE src)
