#ifndef BEETCHEF_JACK_AUDIO_INTERFACE
#define BEETCHEF_JACK_AUDIO_INTERFACE

#include "jack_client.hpp"
#include "jack_port.hpp"

#include "audio/audio_types.hpp"
#include "audio/callback_function.hpp"

#include <memory>
#include <vector>

class Jack_audio_interface {
    public:
        Jack_audio_interface(Jack_client*, int in_chan_count = 2, int out_chan_count = 2);
        nframes_t get_sample_rate();
        sample_t* get_in_buf(int chan_idx, nframes_t nframes) /*const*/;
        sample_t* get_out_buf(int chan_idx, nframes_t nframes);
        void register_process_callback(Callback_function);
    private:
        Jack_client* _jack_client;
        std::vector<Jack_port> _in_ports;
        std::vector<Jack_port> _out_ports;
        Callback_function _callback;

        void connect_io_ports() const;
};

#endif // BEETCHEF_JACK_AUDIO_INTERFACE
