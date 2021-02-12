#include "../headers/client.h"

Client::Client()
{
    socketHandler_.openSocket();
    socketHandler_.bind(CLIENT_PORT);
    socketHandler_.connect(SERVER_PORT, "127.0.0.1");
}

void Client::send()
{
    echoMessage_ = std::make_shared<IcmpPacket> (8,0,0,getpid(),1,"Hello from client!");
    echoMessage_->setChecksum(IcmpPacket::computeChecksum(echoMessage_));
    sleep(1);
    socketHandler_.send(echoMessage_->encode());
    Client::receive();
}

void Client::receive()
{
    std::shared_ptr<std::vector<uint8_t>> reply_buffer = std::make_shared<std::vector<uint8_t>>(26,0);
    socketHandler_.recv(reply_buffer);
    echoMessage_ = IcmpPacket::decode(reply_buffer);
    Utils::displayInfo(echoMessage_, "ON CLIENT ECHO_REPLY  ");
}