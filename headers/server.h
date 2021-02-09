//
// Created by jonasalbuquerque on 09/02/2021.
//

#ifndef PING_SERVER_H
#define PING_SERVER_H

#include "IcmpPacket.h"

class Server {
public:
    int connect();
    void listen();
    void reply();

private:
    std::shared_ptr<IcmpPacket> echoRequest_;
    IcmpPacket echoReply_;
    int socket_;
    struct sockaddr_in serverAddr_, clientAddr_;
};

#endif //PING_SERVER_H
