#include <utils.h>

void Utils::displayInfo(std::shared_ptr <IcmpPacket> packet, std::string extra_msg)
{
    std::cout   << extra_msg
                << " type="         << unsigned(packet->getType())
                << " code="         << unsigned(packet->getCode())
                << " checksum="     << packet->getChecksum()
                << " identifier="   << packet->getIdentifier()
                << " sequence="     << packet->getSequenceNumber()
                << " payload=\""    << packet->getPayload()  << "\""
                << std::endl;
}
