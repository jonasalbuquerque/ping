#include <IcmpPacket.h>
#include "gtest/gtest.h"

TEST(IcmpPacketTest, EncodeWorks){
    IcmpPacket mocked_packet;
    mocked_packet.setType(8);
    mocked_packet.setCode(0);
    mocked_packet.setChecksum(50920);
    mocked_packet.setIdentifier(3120);
    mocked_packet.setSequenceNumber(1);
    mocked_packet.setPayload("Hello!");

    std::vector<uint8_t> expected_vector;
    expected_vector.push_back(8);   //type
    expected_vector.push_back(0);   //code
    expected_vector.push_back(198); //checksum first byte
    expected_vector.push_back(232); //checksum second byte
    expected_vector.push_back(12);  //identifier first byte
    expected_vector.push_back(48);  //identifier second byte
    expected_vector.push_back(0);   //sequencenumber first byte
    expected_vector.push_back(1);   //sequencenumber seconde byte

    //UTF-8 encoding
    expected_vector.push_back(72);  //H
    expected_vector.push_back(101);  //e
    expected_vector.push_back(108); //l
    expected_vector.push_back(108); //l
    expected_vector.push_back(111); //o
    expected_vector.push_back(33);  //!

    EXPECT_EQ(mocked_packet.encode(), expected_vector);
}

TEST(IcmpPacketTest, DecodeWorks){
    std::vector<uint8_t> entry;
    entry.push_back(8);   //type
    entry.push_back(0);   //code
    entry.push_back(198); //checksum first byte
    entry.push_back(232); //checksum second byte
    entry.push_back(12);  //identifier first byte
    entry.push_back(48);  //identifier second byte
    entry.push_back(0);   //sequencenumber first byte
    entry.push_back(1);   //sequencenumber second byte

    //UTF-8 encoding
    entry.push_back(72);  //H
    entry.push_back(101); //e
    entry.push_back(108); //l
    entry.push_back(108); //l
    entry.push_back(111); //o
    entry.push_back(33);  //!

    std::shared_ptr<IcmpPacket> mocked_pckt = std::make_shared<IcmpPacket>();
    mocked_pckt->setType(8);
    mocked_pckt->setCode(0);
    mocked_pckt->setChecksum(50920);
    mocked_pckt->setIdentifier(3120);
    mocked_pckt->setSequenceNumber(1);
    mocked_pckt->setPayload("Hello!");

    std::shared_ptr<IcmpPacket> decoded_pckt = IcmpPacket::decode(entry);

    EXPECT_EQ(mocked_pckt->getType(),decoded_pckt->getType());
    EXPECT_EQ(mocked_pckt->getCode(), decoded_pckt->getCode());
    EXPECT_EQ(mocked_pckt->getChecksum(),decoded_pckt->getChecksum());
    EXPECT_EQ(mocked_pckt->getIdentifier(),decoded_pckt->getIdentifier());
    EXPECT_EQ(mocked_pckt->getSequenceNumber(),decoded_pckt->getSequenceNumber());
    EXPECT_EQ(mocked_pckt->getPayload(),decoded_pckt->getPayload());
}
