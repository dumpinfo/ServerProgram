/*
 * =====================================================================================
 *
 *       Filename:  client.cpp
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
#include "chat_message.h"
#include "structHeader.h"
#include "JsonObject.h"
#include "SerilizationObject.h"
#include "Protocal.pb.h"

#include <boost/asio.hpp>

#include <chrono>
#include <deque>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <cstdlib>
#include <cassert>

using boost::asio::ip::tcp;

using chat_message_queue = std::deque<chat_message>;


class chat_client {
public:
  chat_client(boost::asio::io_service &io_service,
              tcp::resolver::iterator endpoint_iterator)
      : io_service_(io_service), socket_(io_service) {
    do_connect(endpoint_iterator);
  }

  void write(const chat_message &msg) {
    io_service_.post([this, msg]() {
      bool write_in_progress = !write_msgs_.empty();
      write_msgs_.push_back(msg);
      if (!write_in_progress) {
        do_write();
      }
    });
  }

  void close() {
    io_service_.post([this]() { socket_.close(); });
  }

private:
  void do_connect(tcp::resolver::iterator endpoint_iterator) {
    boost::asio::async_connect(
        socket_, endpoint_iterator,
        [this](boost::system::error_code ec, tcp::resolver::iterator) {
          if (!ec) {
            do_read_header();
          }
        });
  }

  void do_read_header() {
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(read_msg_.data(), chat_message::header_length),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec && read_msg_.decode_header()) {
            do_read_body();
          } else {
            socket_.close();
          }
        });
  }

  void do_read_body() {
    boost::asio::async_read(
        socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            if (read_msg_.type() == MT_ROOM_INFO) {
              //SRoomInfo info;
						std::string buffer(read_msg_.body(),
                              read_msg_.body() + read_msg_.body_length());

						PRoomInformation roomInfo;
						auto ok = roomInfo.ParseFromString(buffer);
						//if(!ok) throw std::runtime_error("not valid message");
              //std::stringstream ss(buffer);
							//ptree tree;
							//boost::property_tree::read_json(ss, tree);
						if (ok) {
						std::cout << "client: '";
						std::cout << roomInfo.name();
						std::cout << "' says '";
						std::cout
						<< roomInfo.information();
						std::cout << "'\n";
						}
//              boost::archive::text_iarchive ia(ss);
//              ia & info;
//              std::cout << "client: '";
//              std::cout << info.name();
//              std::cout << "' says '";
//              std::cout << info.information();
//              std::cout << "'\n";
            }
            do_read_header();
          } else {
            socket_.close();
          }
        });
  }

  void do_write() {
    boost::asio::async_write(
        socket_, boost::asio::buffer(write_msgs_.front().data(),
                                     write_msgs_.front().length()),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            write_msgs_.pop_front();
            if (!write_msgs_.empty()) {
              do_write();
            }
          } else {
            socket_.close();
          }
        });
  }

private:
  boost::asio::io_service &io_service_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

int main(int argc, char *argv[]) {
  try {
		GOOGLE_PROTOBUF_VERIFY_VERSION;
    if (argc != 3) {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;
		std::vector<std::unique_ptr<chat_client>> clientGroup;

    tcp::resolver resolver(io_service);
    auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});
		for(int i = 0; i < 10; ++i) {
			clientGroup.emplace_back(std::make_unique<chat_client>(
						io_service, endpoint_iterator));
		}

    std::thread t([&io_service]() { io_service.run(); });

    char line[chat_message::max_body_length + 1];
		// ctrl-d
    while (std::cin.getline(line, chat_message::max_body_length + 1)) {
      chat_message msg;
			auto type = 0;
			std::string input(line, line + std::strlen(line));
			std::string output;
			if(parseMessage4(input, &type, output)) {
				msg.setMessage(type, output.data(), output.size());
				for(auto& v : clientGroup)
					v->write(msg);
				std::cout << "write message for server " << output.size() << std::endl;
			}
    }

		for(auto& v: clientGroup)
			v->close();
    t.join();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

	google::protobuf::ShutdownProtobufLibrary();
  return 0;
}

