// GDPARCM_HO8 - gRPC Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GreeterServer.h"
#include "GreeterClient.h"

#include <thread>

int main()
{
    //run the server
    GreeterServer server;
    server.start();

    //wait for server to startup
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    //run the client
    //GreeterClient::runClient();

    
    struct Data {
    public :
        std::string name;        
        int repetitions;
        std::string message;

        Data(const std::string& n, int r, const std::string& m)
            : name(n), repetitions(r), message(m) {}
    };


    std::vector<Data> users = {
        Data("Charles", 8, "Sir, di gumagana yung gRPC"),
        Data("John", 3, "Chill tayo"),
        Data("Spammer", 10, "Spam mo lang"),
        Data("Jenny", 2, "Two twice"),
        Data("Simon", 6, "Your number one fan!!!"),
        Data("Loki", 6, "Your number one fan!!!"),
        Data("Melly", 7, "Make it stop"),
        Data("Mike", 5, "Magic mik'n"),
        Data("Po", 9, "Kung fu panda"),
    };

    for (int i = 0; i < users.size(); i++) {
        std::thread([username = users[i].name, repeat = users[i].repetitions, message=users[i].message]() {

            GreeterClient::runClientLooped(username, repeat, message);
                }).detach();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
}
