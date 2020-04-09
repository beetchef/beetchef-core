#ifndef BEETCHEF_JACK_AUDIO_INTERFACE
#define BEETCHEF_JACK_AUDIO_INTERFACE

#include "jack_client.hpp"
#include "jack_port.hpp"

#include <iostream>
#include <memory>
#include <vector>

namespace Jack_audio
{
    class Jack_audio_interface {
        public:
            Jack_audio_interface(Jack_client, int in_chan_count = 2, int out_chan_count = 2);

            template<typename T>
            void set_process_callback(T* callable)
            {
                _jack_client->set_process_callback(callable);
            }

            void unset_process_callback();

            void start_processing();
            void stop_processing();

            Jack_client* get_jack_client();

            jack_nframes_t get_sample_rate() const;

            int get_in_chan_count() const;
            int get_out_chan_count() const;

            jack_default_audio_sample_t* get_in_buf(int chan_idx, jack_nframes_t nframes) const;
            jack_default_audio_sample_t* get_out_buf(int chan_idx, jack_nframes_t nframes) const;

        private:
            std::unique_ptr<Jack_client> _jack_client;
            std::vector<Jack_port> _in_ports;
            std::vector<Jack_port> _out_ports;

            void connect_io_ports() const;
    };

}; // namespace Jack_audio

#endif // BEETCHEF_JACK_AUDIO_INTERFACE
