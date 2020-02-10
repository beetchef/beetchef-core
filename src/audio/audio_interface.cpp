#include "audio_interface.hpp"

nframes_t Audio_interface::get_sample_rate() const
{
    return _pimpl->get_sample_rate();
}

sample_t* Audio_interface::get_in_buf(int chan_idx, nframes_t nframes_t) const
{
    return _pimpl->get_in_buf(chan_idx, nframes_t);
}

sample_t* Audio_interface::get_out_buf(int chan_idx, nframes_t nframes_t) const
{
    return _pimpl->get_out_buf(chan_idx, nframes_t);
}
