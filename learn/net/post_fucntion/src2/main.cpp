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
	std::cout << "thread id is ";
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	std::cout << std::this_thread::get_id() << std::endl;
 	std::cout << "func called, i= " << i << std::endl;
}
void workerThread(io_service* service) { service->run(); }

int main(int argc, char** argv) {
  boost::asio::io_service ioService;
  strand one(ioService);
  strand two(ioService);
	for (int i = 0; i < 10; ++i) {
		if (i % 2 == 0)
			ioService.post(one.wrap([i]{ func(i); }));
		else
			ioService.post(two.wrap([i]{ func(i); }));
	}

  std::vector<std::thread> threadGroup;
  for (int i = 0; i < 3; ++i) {
    threadGroup.emplace_back([&ioService] { workerThread(&ioService); });
  }

  for (auto& v : threadGroup) v.join();
}

