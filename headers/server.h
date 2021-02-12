//
// Created by jonasalbuquerque on 09/02/2021.
//

#ifndef PING_SERVER_H
#define PING_SERVER_H

#include "IcmpPacket.h"
#include "sockethandler.h"
#include "utils.h"

class Server {
public:
    Server();
    void listen();
    void reply();
private:
    SocketHandler socketHandler_;
    std::shared_ptr<IcmpPacket> echoMessage_;
};

#endif //PING_SERVER_H
