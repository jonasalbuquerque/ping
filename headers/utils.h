#ifndef PING_UTILS_H
#define PING_UTILS_H

#include <iostream>
#include <memory>
#include "IcmpPacket.h"

class Utils {
public:
    static void displayInfo(std::shared_ptr<IcmpPacket> packet, std::string extra_msg);
};


#endif //PING_UTILS_H
