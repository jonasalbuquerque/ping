# Ping Application

Simple ping application with two threads (client and server) that communicate.

The client side:

1. encodes a object IcmpPacket in a vector of bytes and sends it by a socket;
2. waits for a reply in the same socket;
3. decodes the array of bytes received and displays the packet data;

The server side:

1. waits for a ping request in a socket;
2. decodes the array of bytes received and stores the data in a IcmpPacket object;
3. encodes a IcmpPacket reply object and sends it by the same socket;