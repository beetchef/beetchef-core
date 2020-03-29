add_library(
    jack_audio_base STATIC

    src/jack_audio_interface.cpp
    src/jack_client.cpp
    src/jack_impl_provider.cpp
    src/jack_port.cpp
)

set_target_properties(
    jack_audio_base PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_options(jack_audio_base PUBLIC "-ljack")
target_link_options(jack_audio_base PUBLIC "-lpthread")

target_include_directories(jack_audio_base PUBLIC include)
target_include_directories(jack_audio_base PRIVATE src)
