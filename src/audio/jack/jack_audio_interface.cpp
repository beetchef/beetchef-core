#include "audio/audio_types.hpp"
#include "jack_audio_interface.hpp"
#include "jack_client.hpp"

#include <memory>
#include <string>

Jack_audio_interface::Jack_audio_interface(Jack_client* jack_client, int in_chan_count, int out_chan_count)
    : _jack_client{jack_client}
{
    for (int i = 0; i < in_chan_count; i++) {
        std::string suffix = "_" + std::to_string(i + 1);
        _in_ports.push_back(_jack_client->register_input_port("main_in" + suffix));
    }
    for (int i = 0; i < out_chan_count; i++) {
        std::string suffix = "_" + std::to_string(i + 1);
        _out_ports.push_back(_jack_client->register_output_port("main_out" + suffix));
    }
}

nframes_t Jack_audio_interface::get_sample_rate()
{
    return _jack_client->get_sample_rate();
}

sample_t* Jack_audio_interface::get_in_buf(int chan_idx, nframes_t nframes) /*const*/
{
    return static_cast<sample_t*>(jack_port_get_buffer(_in_ports[chan_idx].get(), nframes));
}

sample_t* Jack_audio_interface::get_out_buf(int chan_idx, nframes_t nframes)
{
    return static_cast<sample_t*>(jack_port_get_buffer(_out_ports[chan_idx].get(), nframes));
}

void Jack_audio_interface::register_process_callback(Callback_function callback)
{
    _callback = std::move(callback);
    _jack_client->set_process_callback(_callback);
    _jack_client->activate();
    connect_io_ports();
}

void Jack_audio_interface::connect_io_ports() const
{
    for (int i = 0; i < _in_ports.size(); i++) {
        std::string suffix = "_" + std::to_string(i + 1);
        _jack_client->connect_ports("system", "capture" + suffix, "beetchef", "main_in" + suffix);
    }
    for (int i = 0; i < _out_ports.size(); i++) {
        std::string suffix = "_" + std::to_string(i + 1);
        _jack_client->connect_ports("beetchef", "main_out" + suffix, "system", "playback" + suffix);
    }
}


