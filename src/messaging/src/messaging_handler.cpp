#include "messaging/messaging_handler.hpp"

#include "ip/UdpSocket.h"
#include "osc/OscOutboundPacketStream.h"

#include <iostream>
#include <string>

using Messaging::Messaging_handler;

Messaging_handler::Messaging_handler() : _transmit_socket(IpEndpointName(address.c_str(), port))
{
    std::cout << log_label << "Created..." << "\n";
}

void Messaging_handler::send_message(std::string address, std::string command)
{
    char buffer[output_buffer_size];
    osc::OutboundPacketStream p(buffer, output_buffer_size);

    p << osc::BeginBundleImmediate
        << osc::BeginMessage(address.c_str())
            << command.c_str() << osc::EndMessage
        << osc::EndBundle;

    std::cout << log_label << "Sending OSC message to SL-engine - address: \"" << address << "\" command: \"" << command << "\"." << "\n";

    _transmit_socket.Send(p.Data(), p.Size());
}
