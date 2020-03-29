#ifndef BEETCHEF_MESSAGING_HANDLER_HPP
#define BEETCHEF_MESSAGING_HANDLER_HPP

#include "ip/UdpSocket.h"

#include <iostream>
#include <string>

class Messaging_handler {
    public:
        Messaging_handler();
        void send_message(std::string address, std::string param);
    private:
        static constexpr std::string_view log_label{"[messaging handler]: "};
        inline static const std::string address{"127.0.0.1"};
        static constexpr int port = 9951;
        static constexpr int output_buffer_size = 1024;
        UdpTransmitSocket _transmit_socket;
};

#endif // BEETCHEF_MESSAGING_HANDLER_HPP