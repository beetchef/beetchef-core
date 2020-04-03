#ifndef BEETCHEF_JACK_AUDIO_INTERFACE
#define BEETCHEF_JACK_AUDIO_INTERFACE

#include "jack_client.hpp"
#include "jack_port.hpp"

#include <memory>
#include <vector>

class Jack_audio_interface {
    public:
        Jack_audio_interface(Jack_client*, int in_chan_count = 2, int out_chan_count = 2);
        jack_nframes_t get_sample_rate() const;

        int get_in_chan_count() const;
        int get_out_chan_count() const;

        jack_default_audio_sample_t* get_in_buf(int chan_idx, jack_nframes_t nframes) const;
        jack_default_audio_sample_t* get_out_buf(int chan_idx, jack_nframes_t nframes) const;

        template<typename T>
        void set_process_callback(T* callback)
        {
            _jack_client->set_process_callback(callback);
            _jack_client->activate();
            connect_io_ports();
        }

    private:
        Jack_client* _jack_client;
        std::vector<Jack_port> _in_ports;
        std::vector<Jack_port> _out_ports;

        void connect_io_ports() const;
};

#endif // BEETCHEF_JACK_AUDIO_INTERFACE
