#include "../headers/server.h"

int Server::connect()
{
    //creates socket file descriptor
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);

    if(socket_ <= 0)
    {
        std::cerr << "SERVER Open Socket Error" << std::endl;
        close(socket_);
        return 0;
    }
    //sets server socket listening on port 5000
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_addr.s_addr = INADDR_ANY;
    serverAddr_.sin_port = htons(5000);

    if (bind(socket_, (struct sockaddr *) &serverAddr_, sizeof(serverAddr_)) < 0)
    {
        std::cerr << "SERVER Binding Error" << std::endl;
        close(socket_);
        return 0;
    }

    //tries connection with client's socket on port 5001
    clientAddr_.sin_family = AF_INET;
    clientAddr_.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddr_.sin_port = htons(5001);

    if (::connect(socket_,
                  (struct sockaddr *) &clientAddr_,
                  sizeof (clientAddr_)) < 0)
    {
        std::cerr << "CLIENT Connect Error" << std::endl;
        close(socket_);
        return 0;
    }

    return 1;
}

void Server::listen()
{
    if (Server::connect()) //if socket's connection was successfully
    {
        std::vector<uint8_t> request_buffer(26,0);

        //waits for response
        int status_recv = recv(socket_,
                               request_buffer.data(),
                               request_buffer.size(),
                               0);

        if(status_recv > 0)
        {
            //decodes icmp header
            echoRequest_ = IcmpPacket::decode(request_buffer);

            std::cout   << "ON SERVER: echo_request:"
                        << " type="         << unsigned(echoRequest_->getType())
                        << " code="         << unsigned(echoRequest_->getCode())
                        << " checksum="     << echoRequest_->getChecksum()
                        << " identifier="   << echoRequest_->getIdentifier()
                        << " sequence="     << echoRequest_->getSequenceNumber()
                        << " payload=\""   << echoRequest_->getPayload()  << "\""
                        << std::endl;

            Server::reply();
        }
        else
        {
            std::cerr << "SERVER Listen Error" << std::endl;
            close(socket_);
        }
    }
}

void Server::reply()
{
    //fills icmp header for reply (same as request but type 0)
    echoReply_ = echoRequest_.operator*();
    echoReply_.setType(0);
    echoReply_.setPayload("Hello from server!");

    //encodes icmp header
    auto reply_buffer = echoReply_.encode();

    //waits for client recv
    sleep(1);

    //sends datagram by the socket
    int actionSendResult = send(socket_,
                                reply_buffer.data(),
                                reply_buffer.size(),
                                0);

    if(actionSendResult < 0)
    {
        std::cerr << "SERVER Reply Error" << std::endl;
        close(socket_);
    }

    close(socket_);
}