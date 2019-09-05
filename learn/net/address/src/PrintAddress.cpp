/*
 * =====================================================================================
 *
 *       Filename:  PrintAddress.cpp
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
#include <iostream>
#include <boost/asio.hpp>
int main(int argc, char** argv) {
	using namespace boost::asio;
	boost::asio::io_service ioService;
	ip::tcp::resolver resolver(ioService);
	ip::tcp::resolver::query query("www.yahoo.com", "80");
	ip::tcp::resolver::iterator iter = resolver.resolve(query);
	ip::tcp::endpoint ep = *iter;
	std::cout << ep.address().to_string() << std::endl;
}

