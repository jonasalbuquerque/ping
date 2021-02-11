#ifndef PING_CLIENT_H
#define PING_CLIENT_H

#include "IcmpPacket.h"
#include "sockethandler.h"
#include "utils.h"

class Client {
public:
    Client();
    void send();
    void receive();
private:
    SocketHandler socketHandler_;
    IcmpPacket echoRequest_;
    std::shared_ptr<IcmpPacket> echoReply_;
};



#endif //PING_CLIENT_H
