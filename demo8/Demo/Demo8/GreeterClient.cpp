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

std::string GreeterClient::SayHelloAgain(const std::string& user)
{
    // Follows the same pattern as SayHello.
    HelloRequest request;
    request.set_name(user);
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
    GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string user("GDPARCM Student");
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;

    reply = greeter.SayHelloAgain(user);
    std::cout << "Greeter received: " << reply << std::endl;
}


void GreeterClient::runClientLooped(std::string username, int n_Repetitions)
{
    GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));


    std::string user(username);
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;

    for (int i = 0; i < n_Repetitions; i++) {
        reply = greeter.SayHelloAgain(user);
        std::cout << "Greeter received: " << reply << std::endl;
    }

}
