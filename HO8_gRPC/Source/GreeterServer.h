#pragma once
#include <cstdint>
#include "Proto/helloworld.pb.h"
#include "Proto/helloworld.grpc.pb.h"
#include "IETThread.h"

class GreeterServer final : public Greeter::Service, public IETThread  {
public:
	grpc::Status SayHello(grpc::ServerContext* context, const HelloRequest* request, HelloReply* response) override;
	grpc::Status SayHelloAgain(grpc::ServerContext* context, const HelloRequest* request, HelloReply* response) override;
	static void RunServer(uint16_t port);

	void run() override;
};

