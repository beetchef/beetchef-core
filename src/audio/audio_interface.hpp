#ifndef AUDIO_INTERFACE_HPP
#define AUDIO_INTERFACE_HPP

#include "audio_types.hpp"

class Audio_interface {
    public:
        virtual ~Audio_interface();
        virtual sample_t* get_in_buf(int chan_idx, nframes_t nframes) = 0;
        virtual sample_t* get_out_buf(int chan_idx, nframes_t nframes) = 0;
        virtual void set_process_callback(/* TBD */) = 0;
    protected:
    private:
};

#endif // AUDIO_INTERFACE_HPP
