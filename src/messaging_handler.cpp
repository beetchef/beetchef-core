#include "messaging_handler.hpp"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include <iostream>

#define LOG_LABEL "[Messaging handler]: "

#define ADDRESS "127.0.0.1"
#define PORT 9951

#define OUTPUT_BUFFER_SIZE 1024

Messaging_handler::Messaging_handler() : _transmit_socket(IpEndpointName( ADDRESS, PORT )) {
    std::cout << LOG_LABEL << "created..." << std::endl;
}

void Messaging_handler::send_message(std::string address, std::string command) {

    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

    p << osc::BeginBundleImmediate
        << osc::BeginMessage( address.c_str() )
            << command.c_str() << osc::EndMessage
        << osc::EndBundle;

    std::cout << LOG_LABEL << "sending OSC message to SL-engine - address: \"" << address << "\" command: \"" << command << "\"" << std::endl;

    _transmit_socket.Send( p.Data(), p.Size() );

}
