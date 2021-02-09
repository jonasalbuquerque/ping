//
// Created by jonasalbuquerque on 09/02/2021.
//

#ifndef PING_CLIENT_H
#define PING_CLIENT_H

#include "IcmpPacket.h"

class Client {
public:
    int connect();
    void send();
    void receive();
private:
    IcmpPacket echoRequest_;
    std::shared_ptr<IcmpPacket> echoReply_;
    int socket_;
    struct sockaddr_in serverAddr_, clientAddr_;
};


#endif //PING_CLIENT_H
