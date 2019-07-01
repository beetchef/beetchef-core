#ifndef MESSAGING_HANDLER_HPP
#define MESSAGING_HANDLER_HPP

#include <iostream>
#include "ip/UdpSocket.h"

using std::string;

class MessagingHandler {
    public:
        MessagingHandler();
        void sendMessage(string message);
    private:
        UdpTransmitSocket mTransmitSocket;
        char* mBuffer;
};

#endif
