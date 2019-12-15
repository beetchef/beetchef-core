#ifndef MESSAGING_HANDLER_HPP
#define MESSAGING_HANDLER_HPP

#include <iostream>
#include "ip/UdpSocket.h"

using std::string;

class MessagingHandler {
    public:
        MessagingHandler();
        void send_message(string address, string param);
    private:
        UdpTransmitSocket _transmit_socket;
};

#endif
