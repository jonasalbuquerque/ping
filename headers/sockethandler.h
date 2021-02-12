#ifndef PING_SOCKETHANDLER_H
#define PING_SOCKETHANDLER_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <memory>
#include <stdexcept>
#include <vector>

#define SERVER_PORT 5000
#define CLIENT_PORT 5001

class SocketHandler {
private:
    int socketFd_;
    sockaddr_in srcAddress_, destAddress_;
public:
    void openSocket();
    void bind(const uint16_t &port);
    void connect(const uint16_t &port,
                        const std::string &ip);

    void send(std::shared_ptr<std::vector<uint8_t>> buf);
    void recv(std::shared_ptr<std::vector<uint8_t>> buf);
};

#endif //PING_SOCKETHANDLER_H
