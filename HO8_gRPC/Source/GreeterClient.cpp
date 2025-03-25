#include "GreeterClient.h"
#include <grpcpp/create_channel.h>

GreeterClient::GreeterClient(std::shared_ptr<grpc::ChannelInterface> channel)
{
    this->stub_ = Greeter::NewStub(channel);
}


std::string GreeterClient::SayHello(const std::string& user)
{
    // Follows the same pattern as SayHello.
    HelloRequest request;
    request.set_name(user);

    HelloReply reply;
    grpc::ClientContext context;

    std::chrono::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::milliseconds(2000);
    context.set_deadline(deadline);

    // Here we can use the stub's newly available method we just added.
    grpc::Status status = stub_->SayHello(&context, request, &reply);
    if (status.ok()) {
        return reply.message();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        return "RPC failed";
    }
}

std::string GreeterClient::SayHelloAgain(const std::string& user, const std::string& message)
{
    // Follows the same pattern as SayHello.
    HelloRequest request;
    request.set_name(user);
    request.set_chat_msg(message);

    HelloReply reply;
    grpc::ClientContext context;

    // Here we can use the stub's newly available method we just added.
    grpc::Status status = stub_->SayHelloAgain(&context, request, &reply);
    if (status.ok()) {
        return reply.message();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        return "RPC failed";
    }
}

void GreeterClient::runClient()
{
    /*GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string user("GDPARCM Student");
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;

    reply = greeter.SayHelloAgain(user);
    std::cout << "Greeter received: " << reply << std::endl;*/
}


void GreeterClient::runClientLooped(const std::string& username, int n_Repetitions, const std::string& message)
{
    std::random_device rd;  // Obtain a random number from the hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> dis(100, 5000);  // Define the range (1 to 5 seconds)

    // Generate a random delay between 1 and 5 seconds
    int random_seconds = dis(gen);



    GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));


    std::string user(username);
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;

    for (int i = 0; i < n_Repetitions; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(random_seconds));

        reply = greeter.SayHelloAgain(user, message);
        std::cout << "Greeter received: " << reply << std::endl;
    }

}
