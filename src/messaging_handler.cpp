#include "messaging_handler.hpp"
#include "ip/UdpSocket.h"
#include "osc/OscOutboundPacketStream.h"

#include <iostream>
#include <string>

Messaging_handler::Messaging_handler() : _transmit_socket(IpEndpointName(address.c_str(), port))
{
    std::cout << log_label << "created..." << std::endl;
}

void Messaging_handler::send_message(std::string address, std::string command)
{
    char buffer[output_buffer_size];
    osc::OutboundPacketStream p(buffer, output_buffer_size);

    p << osc::BeginBundleImmediate
        << osc::BeginMessage(address.c_str())
            << command.c_str() << osc::EndMessage
        << osc::EndBundle;

    std::cout << log_label << "sending OSC message to SL-engine - address: \"" << address << "\" command: \"" << command << "\"" << std::endl;

    _transmit_socket.Send(p.Data(), p.Size());
}
