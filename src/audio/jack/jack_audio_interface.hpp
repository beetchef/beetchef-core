#ifndef BEETCHEF_JACK_AUDIO_INTERFACE
#define BEETCHEF_JACK_AUDIO_INTERFACE

#include "audio/audio_types.hpp"
#include "jack_client.hpp"
#include "jack_port_handle.hpp"

#include <memory>
#include <vector>

class Jack_audio_interface {
    public:
        Jack_audio_interface(Jack_client*, int in_chan_count = 2, int out_chan_count = 2);
        nframes_t get_sample_rate();
        sample_t* get_in_buf(int chan_idx, nframes_t nframes) /*const*/;
        sample_t* get_out_buf(int chan_idx, nframes_t nframes);
        void set_process_callback(/* TBD */);
    private:
        static constexpr std::string_view log_label{"[JACK audio interface]: "};
        Jack_client* _jack_client;
        std::vector<Jack_port_handle> _in_ports;
        std::vector<Jack_port_handle> _out_ports;
};

#endif // BEETCHEF_JACK_AUDIO_INTERFACE
