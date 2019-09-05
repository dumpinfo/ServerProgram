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
//#include <time.h>
#include <ctime>

#include <iostream>
#include <string>

#include <boost/asio.hpp>

//#include "gameDefine.h"

using boost::asio::ip::tcp;

std::string make_daytime_string() {
  using namespace std; // For time_t, time and ctime;
  auto now = time(nullptr);
  return ctime(&now); // const char*
}

int main() {
  try {
    boost::asio::io_service io_service;

		// 127.0.0.1
		// *
		// root linux < 1024
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
		std::cout << "start service\n";

    for (;;) {
			// 10.34.32.*
      tcp::socket socket(io_service);
      acceptor.accept(socket);

      auto message = make_daytime_string();

			//boost::array
      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
		std::cout << "bye\n";
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
