// GrpcPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <grpcpp/grpcpp.h>

#include "EchoService.h"

void grpcFunction(std::future<void> cancellationTokenSource)
{
	std::string server_address("127.0.0.1:4566");

	// Start GRPC server
	std::cout << "Starting GRPC" << std::endl;

	EchoServiceImpl echoService;

	grpc::ServerBuilder serverBuilder;
	serverBuilder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	serverBuilder.RegisterService(&echoService);

	std::unique_ptr<grpc::Server> server(serverBuilder.BuildAndStart());
	
	cancellationTokenSource.wait();

	server->Shutdown();
	server->Wait();

	// Stop GRPC server
	std::cout << "Stopping GRPC" << std::endl;
}

int main()
{
	std::promise<void> cancellationToken;
	std::future<void> cancellationTokenSource = cancellationToken.get_future();

	// Look at health monitor code
	std::thread grpcThread(&grpcFunction, std::move(cancellationTokenSource));

	cancellationToken.set_value();

	grpcThread.join();

	return 0;
}
