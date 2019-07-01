#include "messaging_handler.hpp"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include <iostream>

#define LOG_LABEL "[Messaging handler]: "

#define ADDRESS "127.0.0.1"
#define PORT 9951

#define OUTPUT_BUFFER_SIZE 1024

using std::cout;
using std::endl;
using std::string;

MessagingHandler::MessagingHandler() : mTransmitSocket(IpEndpointName( ADDRESS, PORT )) {
    cout << LOG_LABEL << "created..." << endl;
}

void MessagingHandler::sendMessage(string address, string command) {
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( address.c_str() )
            << command.c_str() << osc::EndMessage
        << osc::EndBundle;
    
    cout << LOG_LABEL << "sending OSC message to SL-engine - address: \"" << address << "\" command: \"" << command << "\"" << endl;

    mTransmitSocket.Send( p.Data(), p.Size() );

    // UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    // char buffer[OUTPUT_BUFFER_SIZE];
    // osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    // p << osc::BeginBundleImmediate
    //     << osc::BeginMessage( "/test1" ) 
    //         << true << 23 << (float)3.1415 << "hello" << osc::EndMessage
    //     << osc::BeginMessage( "/test2" ) 
    //         << true << 24 << (float)10.8 << "world" << osc::EndMessage
    //     << osc::EndBundle;
    
    // transmitSocket.Send( p.Data(), p.Size() );
}
