#include <thread>

#include "../headers/client.h"
#include "../headers/server.h"

void start_server()
{
    try
    {
        Server g_server;
        g_server.listen();
    }
    catch (const std::exception& e)
    {
        std::string error_msg = "ON SERVER: ";
        error_msg.append(e.what());
        throw std::runtime_error(error_msg);
    }
}

void start_client()
{
    try
    {
        Client g_client;
        g_client.send();
    }
    catch (const std::exception& e)
    {
        std::string error_msg = "ON CLIENT: ";
        error_msg.append(e.what());
        throw std::runtime_error(error_msg);
    }
}

int main()
{
    try
    {
        std::thread th_server (start_server);
        std::thread th_client (start_client);

        th_server.join();
        th_client.join();

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
