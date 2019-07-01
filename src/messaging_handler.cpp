#include "messaging_handler.hpp"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include <iostream>

#define LOG_LABEL "[Messaging handler]: "

#define ADDRESS "127.0.0.1"
#define PORT 7000

#define OUTPUT_BUFFER_SIZE 1024

using std::cout;
using std::endl;
using std::string;

MessagingHandler::MessagingHandler() : mTransmitSocket(IpEndpointName( ADDRESS, PORT )) {
    cout << LOG_LABEL << "created..." << endl;
    mBuffer[OUTPUT_BUFFER_SIZE];
}

void MessagingHandler::sendMessage(string message) {
    
    osc::OutboundPacketStream p( mBuffer, OUTPUT_BUFFER_SIZE );
    
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/test1" ) 
            << "/sl/0/hit s:record" << osc::EndMessage
        
        << osc::EndBundle;
    
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
