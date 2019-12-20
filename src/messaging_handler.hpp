#ifndef MESSAGING_HANDLER_HPP
#define MESSAGING_HANDLER_HPP

#include "ip/UdpSocket.h"

#include <iostream>

class Messaging_handler {
    public:
        Messaging_handler();
        void send_message(std::string address, std::string param);
    private:
        UdpTransmitSocket _transmit_socket;
};

#endif
