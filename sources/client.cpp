#include "../headers/client.h"

Client::Client()
{
    socketHandler_.openSocket();
    socketHandler_.bind(CLIENT_PORT);
    socketHandler_.connect(SERVER_PORT, "127.0.0.1");
}

void Client::send()
{
    echoRequest_ = IcmpPacket(8,
                              0,
                              0,
                              getpid(),
                              1,
                              "Hello from client!");

    echoRequest_.setChecksum(IcmpPacket::computeChecksum(echoRequest_));

    auto request_buffer = echoRequest_.encode();

    sleep(1);

    socketHandler_.send(request_buffer);

    Client::receive();
}

void Client::receive()
{
    std::vector<uint8_t> reply_buffer(26,0);

    socketHandler_.recv(reply_buffer);

    echoReply_ = IcmpPacket::decode(reply_buffer);

    Utils::displayInfo(echoReply_, "ON CLIENT ECHO_REPLY");
}