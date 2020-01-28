#include "jack_audio_interface.hpp"

#include "jack_port_handle.hpp"
#include "jack_client_wrapper.hpp"

#include <memory>

Jack_audio_interface::Jack_audio_interface(Jack_client_wrapper* client)
    : _client{client}
{
}

sample_t* Jack_audio_interface::get_in_buf(int chan_idx, nframes_t nframes)
{
    return static_cast<sample_t*>(jack_port_get_buffer(_in_ports[chan_idx].get(), nframes));
}

sample_t* Jack_audio_interface::get_out_buf(int chan_idx, nframes_t nframes)
{
    return static_cast<sample_t*>(jack_port_get_buffer(_out_ports[chan_idx].get(), nframes));
}

void Jack_audio_interface::set_process_callback(/* TBD */)
{
    _client->set_process_callback(/* TBD */);
}


