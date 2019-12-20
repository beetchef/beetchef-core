#ifndef MESSAGING_HANDLER_HPP
#define MESSAGING_HANDLER_HPP

#include <iostream>
#include "ip/UdpSocket.h"

using std::string;

class Messaging_handler {
    public:
        Messaging_handler();
        void send_message(string address, string param);
    private:
        UdpTransmitSocket _transmit_socket;
};

#endif
