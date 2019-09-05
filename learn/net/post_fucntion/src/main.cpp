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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "thread id is " << std::this_thread::get_id() << std::endl;
 	std::cout << "func called, i= " << i << std::endl;
}
void workerThread(io_service* service) { service->run(); }

int main(int argc, char** argv) {
	boost::asio::io_service ioService;
	for(int i = 0; i < 10; ++i) {
		ioService.post([i]() { func(i);});
	}

	std::vector<std::thread> threadGroup;
	for(int i = 0; i < 3; ++i) {
		threadGroup.emplace_back([&ioService] { workerThread(&ioService);});
	}

	for(auto& v : threadGroup) v.join();
}

