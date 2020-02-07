#include "audio/audio_types.hpp"
#include "jack_audio_interface.hpp"
#include "jack_client.hpp"

#include <memory>

Jack_audio_interface::Jack_audio_interface(Jack_client* jack_client, int in_chan_count, int out_chan_count)
    : _jack_client{jack_client}
{

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

void Jack_audio_interface::set_process_callback(/* TBD */)
{
    _jack_client->set_process_callback(/* TBD */);
}


