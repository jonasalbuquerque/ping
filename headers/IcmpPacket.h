#ifndef PING_ICMPPACKET_H
#define PING_ICMPPACKET_H

// The wire format of an ICMP header is:
//
// 0               8               16                             31
// +---------------+---------------+------------------------------+      ---
// |               |               |                              |       ^
// |     type      |     code      |          checksum            |       |
// |               |               |                              |       |
// +---------------+---------------+------------------------------+    8 bytes
// |                               |                              |       |
// |          identifier           |       sequence number        |       |
// |                               |                              |       v
// +-------------------------------+------------------------------+      ---

#include <iostream>
#include <vector>
#include <unistd.h>
#include <memory>

class IcmpPacket {
private:
    uint8_t type_{};
    uint8_t code_{};
    uint16_t checksum_{};
    uint16_t identifier_{};
    uint16_t sequenceNumber_{};
    std::string payload_;

public:
    IcmpPacket();
    IcmpPacket(uint8_t p_type,
               uint8_t p_code,
               uint16_t p_checksum,
               uint16_t p_identifier,
               uint16_t p_sequenceNumber,
               std::string p_payload
    );
    std::vector<uint8_t> encode();
    static std::shared_ptr<IcmpPacket> decode(const std::vector<uint8_t> &inputPacket);

    uint8_t getType() const;
    uint8_t getCode() const;
    uint16_t getChecksum() const;
    uint16_t getIdentifier() const;
    uint16_t getSequenceNumber() const;
    std::string getPayload() const;

    void setType(const uint8_t &newType);
    void setCode(const uint8_t &newCode);
    void setChecksum(const uint16_t &newChecksum);
    void setIdentifier(const uint16_t &newIdentifier);
    void setSequenceNumber(const uint16_t &newSequenceNumber);
    void setPayload(const std::string &newPayload);

    static uint16_t computeChecksum(IcmpPacket &packet);
};


#endif //PING_ICMPPACKET_H
