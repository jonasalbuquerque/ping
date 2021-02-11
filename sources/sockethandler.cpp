#include "sockethandler.h"

void SocketHandler::openSocket()
{
    if((socketFd_ = ::socket(AF_INET, SOCK_DGRAM, 0)) <= 0)
    {
        throw std::runtime_error("Socket Error");
    }
}

void SocketHandler::bind(const uint16_t &port)
{
    srcAddress_.sin_family = AF_INET;
    srcAddress_.sin_addr.s_addr = INADDR_ANY;
    srcAddress_.sin_port = htons(port);

    if (::bind(socketFd_, (struct sockaddr *) &srcAddress_, sizeof(srcAddress_)) < 0)
    {
        throw std::runtime_error("Bind Error");
    }
}

void SocketHandler::connect(const uint16_t &port, const std::string &ip)
{
    destAddress_.sin_family = AF_INET;
    destAddress_.sin_addr.s_addr = inet_addr(ip.data());
    destAddress_.sin_port = htons(port);

    if (::connect(socketFd_,
                  (struct sockaddr *) &destAddress_,
                  sizeof (destAddress_)) < 0)
    {
        throw std::runtime_error("Connect Error");
    }
}

void SocketHandler::send(std::vector<uint8_t> &buf)
{
    if (::send(socketFd_, buf.data(), buf.size(),0) < 0)
    {
        throw std::runtime_error("Send Error");
    }
}

void SocketHandler::recv(std::vector<uint8_t> &buf)
{
    if (::recv(socketFd_, buf.data(), buf.size(),0) < 0)
    {
        throw std::runtime_error("Receive Error");
    }
}

