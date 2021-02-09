
#include "../headers/client.h"

int Client::connect()
{
    //creates socket file descriptor
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);

    if(socket_ <= 0)
    {
        std::cerr << "CLIENT Open Socket Error" << std::endl;
        close(socket_);
        return 0;
    }

    //sets client socket listening on port 5001
    clientAddr_.sin_family = AF_INET;
    clientAddr_.sin_addr.s_addr = INADDR_ANY;
    clientAddr_.sin_port = htons(5001);
    if (bind(socket_, (struct sockaddr *) &clientAddr_, sizeof(clientAddr_)) < 0)
    {
        std::cerr << "SERVER Binding Error" << std::endl;
        close(socket_);
        return 0;
    }

    //tries connection with server's socket on port 5000
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr_.sin_port = htons(5000);

    if (::connect(socket_,
                  (struct sockaddr *) &serverAddr_,
                  sizeof (serverAddr_)) < 0)
    {
        std::cerr << "CLIENT Connect Error" << std::endl;
        close(socket_);
        return 0;
    }
    return 1;
}

void Client::send()
{
    if (Client::connect()) //if socket's connection was successfully
    {
        //fills icmp header for request
        echoRequest_ = IcmpPacket(8,
                                  0,
                                  0,
                                  getpid(),
                                  1,
                                  "Hello from client!");

        echoRequest_.setChecksum(IcmpPacket::computeChecksum(echoRequest_));

        //encodes icmp header
        auto request_buffer = echoRequest_.encode();

        //waits for server recv
        sleep(1);

        //sends datagram by the socket
        int status_send = ::send(socket_,
                                 request_buffer.data(),
                                 request_buffer.size(),
                                 0);

        if(status_send < 0)
        {
            std::cerr << "CLIENT Send Error" << std::endl;
            close(socket_);
            return;
        }

        //starts receive
        Client::receive();
    }
}

void Client::receive()
{
    std::vector<uint8_t> reply_buffer(26,0);

    //waits for response
    int status_recv = recv(socket_,
                           reply_buffer.data(),
                           reply_buffer.size(),
                           0);

    if(status_recv > 0)
    {
        //decodes icmp header and stores payload
        echoReply_ = IcmpPacket::decode(reply_buffer);


        std::cout   << "ON CLIENT: echo_reply:"
                    << " type="         << unsigned(echoReply_->getType())
                    << " code="         << unsigned(echoReply_->getCode())
                    << " checksum="     << echoReply_->getChecksum()
                    << " identifier="   << echoReply_->getIdentifier()
                    << " sequence="     << echoReply_->getSequenceNumber()
                    << " payload=\""    << echoReply_->getPayload() << "\""
                    << std::endl;
    }
    else
    {
        std::cerr << "CLIENT Receive Error" << std::endl;
        close(socket_);
    }
    close(socket_);
}
