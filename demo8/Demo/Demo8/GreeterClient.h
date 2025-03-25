#pragma once
#include <string>
#include "Proto/helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class GreeterClient
{
public:
	GreeterClient(std::shared_ptr<grpc::ChannelInterface> channel);
	std::string SayHello(const std::string& user);
	std::string SayHelloAgain(const std::string& user, const std::string& message);

	static void runClient();
	static void runClientLooped(const std::string& username, int n_Repetitions, const std::string& msg);

private:
	std::unique_ptr<Greeter::Stub> stub_;
};

