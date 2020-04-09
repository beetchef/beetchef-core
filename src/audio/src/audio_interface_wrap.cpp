#include "audio/audio_interface_wrap.hpp"
#include "audio/types.hpp"

void Audio_interface_wrap::start_processing()
{
    _audio_interface->start_processing();
}

void Audio_interface_wrap::stop_processing()
{
    _audio_interface->stop_processing();
}

nframes_t Audio_interface_wrap::get_sample_rate() const
{
    return _audio_interface->get_sample_rate();
}

int Audio_interface_wrap::get_in_chan_count() const
{
    return _audio_interface->get_in_chan_count();
}

int Audio_interface_wrap::get_out_chan_count() const
{
    return _audio_interface->get_out_chan_count();
}

sample_t* Audio_interface_wrap::get_in_buf(int chan_idx, nframes_t nframes_t) const
{
    return _audio_interface->get_in_buf(chan_idx, nframes_t);
}

sample_t* Audio_interface_wrap::get_out_buf(int chan_idx, nframes_t nframes_t) const
{
    return _audio_interface->get_out_buf(chan_idx, nframes_t);
}

void Audio_interface_wrap::unregister_process_callback()
{
    _callback = Callback_function{dummy_callback};
}
