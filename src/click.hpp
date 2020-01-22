#ifndef CLICK_HPP
#define CLICK_HPP

#include "jack_client_wrapper.hpp"
#include "jack_connection_node.hpp"
#include "messaging_handler.hpp"

#include <string>

class Click : public Jack_connection_node {
    public:
        Click(Jack_client_wrapper& jack_client);
        bool init();
        void start();
        void jack_process_callback(jack_nframes_t nframes);
    protected:
    private:
        static constexpr std::string_view log_label{"[click]: "};
        Jack_client_wrapper& _jack_client;
        unsigned int _tempo{60};
        unsigned int _signature_numerator{4};
        unsigned int _signature_denominator{4};
        unsigned int _current_beat{1};
        long _beat_duration;
        long _bar_duration;
        bool _is_running {false};
        Messaging_handler _messaging_handler;
};

#endif // CLICK_HPP
