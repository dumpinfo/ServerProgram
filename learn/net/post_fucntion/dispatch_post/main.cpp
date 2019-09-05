/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <boost/asio.hpp>
using namespace boost::asio;
void func(int i) {
	std::cout << "thread id is " << std::this_thread::get_id() << std::endl;
 	std::cout << "func called, i= " << i << std::endl;
}

void runDispatchAndPost(io_service* ioService) {
	for(int i = 0; i < 10; i += 2) {
		ioService->post([i]{func(i);});
		ioService->dispatch([i]{func(i+1);});
	}
}
//void workerThread(io_service* service) { service->run(); }

int main(int argc, char** argv) {
	boost::asio::io_service ioService;
	ioService.post([&ioService]{runDispatchAndPost(&ioService);});
	ioService.run();
//	std::vector<std::thread> threadGroup;
//	for(int i = 0; i < 3; ++i) {
//		threadGroup.emplace_back([&ioService] { workerThread(&ioService);});
//	}
//
//	for(auto& v : threadGroup) v.join();
}

