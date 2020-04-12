#include "messaging/messaging_handler.hpp"

#include "ip/UdpSocket.h"
#include "osc/OscOutboundPacketStream.h"

#include <string>

#include <spdlog/spdlog.h>

using Messaging::Messaging_handler;

Messaging_handler::Messaging_handler() : _transmit_socket(IpEndpointName(address.c_str(), port))
{
    spdlog::info("{} Created.", log_label);
}

void Messaging_handler::send_message(std::string address, std::string command)
{
    char buffer[output_buffer_size];
    osc::OutboundPacketStream p(buffer, output_buffer_size);

    p << osc::BeginBundleImmediate
        << osc::BeginMessage(address.c_str())
            << command.c_str() << osc::EndMessage
        << osc::EndBundle;

    spdlog::info("{} Sending OSC message to SL-engine - address: \"{}\" command: \"{}\".", log_label, address, command);

    _transmit_socket.Send(p.Data(), p.Size());
}
