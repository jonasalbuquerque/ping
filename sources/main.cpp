#include <thread>

#include "../headers/client.h"
#include "../headers/server.h"

Server g_server;
Client g_client;

void start_server() { g_server.listen(); }

void start_client() { g_client.send(); }

int main(int argc, char* argv[])
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
