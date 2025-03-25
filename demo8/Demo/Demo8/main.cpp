// GDPARCM_HO8 - gRPC Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GreeterServer.h"
#include "GreeterClient.h"

int main()
{
    //run the server
    GreeterServer server;
    server.start();

    //wait for server to startup
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    //run the client
    GreeterClient::runClient();

    GreeterClient::runClient();
}
