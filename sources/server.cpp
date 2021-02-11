#include "../headers/server.h"

Server::Server()
{
    socketHandler_.openSocket();
    socketHandler_.bind(SERVER_PORT);
    socketHandler_.connect(CLIENT_PORT, "127.0.0.1");
}

void Server::listen()
{
    std::vector<uint8_t> request_buffer(26,0);

    socketHandler_.recv(request_buffer);

    echoRequest_ = IcmpPacket::decode(request_buffer);

    Utils::displayInfo(echoRequest_, "ON SERVER ECHO_REQUEST");

    Server::reply();
}

void Server::reply()
{
    echoReply_ = echoRequest_.operator*();
    echoReply_.setType(0);
    echoReply_.setPayload("Hello from server!");

    auto reply_buffer = echoReply_.encode();

    sleep(1);

    socketHandler_.send(reply_buffer);
}