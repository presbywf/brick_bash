// GrpcPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void grpcFunction(std::future<void> cancellationTokenSource)
{
	// Start GRPC server
	std::cout << "Starting GRPC" << std::endl;


	cancellationTokenSource.wait();


	// Stop GRPC server
	std::cout << "Stopping GRPC" << std::endl;

}

int main()
{
	std::promise<void> cancellationToken;
	std::future<void> cancellationTokenSource = cancellationToken.get_future();

	std::thread grpcThread(&grpcFunction, std::move(cancellationTokenSource));

	std::this_thread::sleep_for(std::chrono::seconds(10));

	std::cout << "Sending cancellation token..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));

	cancellationToken.set_value();

	grpcThread.join();

	return 0;
}
