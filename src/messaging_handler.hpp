#ifndef MESSAGING_HANDLER_HPP
#define MESSAGING_HANDLER_HPP

#include <iostream>
#include "ip/UdpSocket.h"

using std::string;

class MessagingHandler {
    public:
        MessagingHandler();
        void sendMessage(string address, string param);
    private:
        UdpTransmitSocket mTransmitSocket;
};

#endif
