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
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <boost/date_time/posix_time/posix_time.hpp>

class printer {
public:
  printer(boost::asio::io_service &io)
      : strand_(io), timer1_(io, boost::posix_time::seconds(1)),
        timer2_(io, boost::posix_time::seconds(1)), count_(0) {
    timer1_.async_wait(strand_.wrap([this](const auto&){this->print1(); }));
    timer2_.async_wait(strand_.wrap([this](const auto&){this->print2(); }));
  }

  ~printer() { std::cout << "Final count is " << count_ << std::endl; }

  void print1() {
    if (count_ < 10) {
      std::cout << "Timer 1: " << count_ << std::endl;
      ++count_;

      timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
      timer1_.async_wait(strand_.wrap([this](const auto&){this->print1(); }));
    }
  }

  void print2() {
    if (count_ < 10) {
      std::cout << "Timer 2: " << count_ << std::endl;
      ++count_;

      timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
      timer2_.async_wait(strand_.wrap([this](const auto&){this->print2(); }));
    }
  }

private:
  boost::asio::io_service::strand strand_;
  boost::asio::deadline_timer timer1_;
  boost::asio::deadline_timer timer2_;
  int count_;
};

int main() {
  boost::asio::io_service io;
  std::thread t([&io] { io.run(); });
  printer p(io);
	if(io.stopped()) {
		io.reset();
	}
  io.run();
  t.join();

  return 0;
}
