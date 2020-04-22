/*
 *  Beetchef - real time audio sequencer
 *  Copyright (C) 2020 Anton Šefčík
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <messaging/messaging_handler.hpp>

#include <ip/UdpSocket.h>
#include <osc/OscOutboundPacketStream.h>

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
