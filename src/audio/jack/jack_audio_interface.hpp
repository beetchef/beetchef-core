#ifndef JACK_AUDIO_INTERFACE
#define JACK_AUDIO_INTERFACE

#include "audio/audio_types.hpp"
#include "jack_client_wrapper.hpp"
#include "jack_port_handle.hpp"

#include <memory>
#include <vector>

class Jack_audio_interface {
    public:
        Jack_audio_interface(Jack_client_wrapper*);
        sample_t* get_in_buf(int chan_idx, nframes_t nframes) /*const*/;
        sample_t* get_out_buf(int chan_idx, nframes_t nframes);
        void set_process_callback(/* TBD */);
    private:
        Jack_client_wrapper* _jack_client;
        std::vector<Jack_port_handle> _in_ports;
        std::vector<Jack_port_handle> _out_ports;
};

#endif // JACK_AUDIO_INTERFACE
