#include "../headers/server.h"

Server::Server()
{
    socketHandler_.openSocket();
    socketHandler_.bind(SERVER_PORT);
    socketHandler_.connect(CLIENT_PORT, "127.0.0.1");
}

void Server::listen()
{
    std::shared_ptr<std::vector<uint8_t>> request_buffer = std::make_shared<std::vector<uint8_t>>(26,0);
    socketHandler_.recv(request_buffer);
    echoMessage_ = IcmpPacket::decode(request_buffer);
    Utils::displayInfo(echoMessage_, "ON SERVER ECHO_REQUEST");
    Server::reply();
}

void Server::reply()
{
    echoMessage_->setType(0);
    echoMessage_->setPayload("Hello from server!");
    sleep(1);
    socketHandler_.send(echoMessage_->encode());
}