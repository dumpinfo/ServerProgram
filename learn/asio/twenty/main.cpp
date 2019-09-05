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
#include "chat_message.h"
#include "JsonObject.h"
#include "Protocal.pb.h"

#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include <chrono>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <mutex>
#include <cstdlib>

using boost::asio::ip::tcp;

//----------------------------------------------------------------------

using chat_message_queue = std::deque<chat_message>;
using chat_message_queue2 = std::list<chat_message>;
//----------------------------------------------------------------------

// stread_clock
std::chrono::system_clock::time_point base;

//----------------------------------------------------------------------

class chat_session;
using chat_session_ptr = std::shared_ptr<chat_session>;
class chat_room {
public:
	chat_room(boost::asio::io_service& io_service) : m_strand(io_service) {}
public:
	void join(chat_session_ptr);
	void leave(chat_session_ptr);
	void deliver(const chat_message&);
private:
	boost::asio::io_service::strand m_strand;
	//std::mutex m_mutex;
  std::set<chat_session_ptr> participants_;
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;
};
//----------------------------------------------------------------------

class chat_session : public std::enable_shared_from_this<chat_session> {
public:
  chat_session(tcp::socket socket, chat_room &room)
      : socket_(std::move(socket)), room_(room),
			m_strand(socket_.get_io_service()) {}

  void start() {
    room_.join(shared_from_this());
    do_read_header();
  }

  void deliver(const chat_message &msg) {
		// first false
		m_strand.post([this, msg]{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress) {
			// first
      do_write();
    }});
  }

private:
  void do_read_header() {
    auto self(shared_from_this());
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(read_msg_.data(), chat_message::header_length),
				m_strand.wrap(
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec && read_msg_.decode_header()) {
            do_read_body();
          } else {
            std::cout << "Player leave the room\n";
            room_.leave(shared_from_this());
          }
        }));
  }

  void do_read_body() {
    auto self(shared_from_this());
    boost::asio::async_read(
        socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				m_strand.wrap(
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            //room_.deliver(read_msg_);
						handleMessage();
            do_read_header();
          } else {
            room_.leave(shared_from_this());
          }
        }));
  }

  template <typename T> T toObject() {
    T obj;
    std::stringstream ss(std::string(
        read_msg_.body(), read_msg_.body() + read_msg_.body_length()));
    boost::archive::text_iarchive oa(ss);
    oa &obj;
    return obj;
  }

  bool fillProtobuf(::google::protobuf::Message* msg) {
    std::string ss(
        read_msg_.body(), read_msg_.body() + read_msg_.body_length());
		auto ok = msg->ParseFromString(ss);
    return ok;
  }

	ptree toPtree() {
		ptree obj;
		std::stringstream ss(
				std::string(read_msg_.body(),
					read_msg_.body() + read_msg_.body_length()));
		boost::property_tree::read_json(ss, obj);
		return obj;
	}

  void handleMessage() {
		auto n = std::chrono::system_clock::now() - base;
		std::cout << "i'm in " << std::this_thread::get_id() << " time "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(n).count() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
    if (read_msg_.type() == MT_BIND_NAME) {
			PBindName bindName;
			if(fillProtobuf(&bindName))
				m_name = bindName.name();
    } else if (read_msg_.type() == MT_CHAT_INFO) {
			PChat chat;
			if(!fillProtobuf(&chat)) return;
			m_chatInformation = chat.information();

      auto rinfo = buildRoomInfo();
      chat_message msg;
      msg.setMessage(MT_ROOM_INFO, rinfo);
      room_.deliver(msg);

    } else {
      // not valid msg do nothing
    }
  }

  void do_write() {
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_, boost::asio::buffer(write_msgs_.front().data(),
                                     write_msgs_.front().length()),
				m_strand.wrap(
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            write_msgs_.pop_front();
            if (!write_msgs_.empty()) {
              do_write();
            }
          } else {
            room_.leave(shared_from_this());
          }
        }));
  }

  tcp::socket socket_;
  chat_room &room_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
	std::string m_name;
	std::string m_chatInformation;
	boost::asio::io_service::strand m_strand;
	std::string buildRoomInfo() const {
		PRoomInformation roomInfo;
		roomInfo.set_name(m_name);
		roomInfo.set_information(m_chatInformation);
		std::string out;
		auto ok = roomInfo.SerializeToString(&out);
		assert(ok);
		return out;
	}
//	RoomInformation buildRoomInfo() const {
//		RoomInformation info;
//		info.name.nameLen = m_name.size();
//		std::memcpy(info.name.name, m_name.data(), m_name.size());
//		info.chat.infoLen = m_chatInformation.size();
//		std::memcpy(info.chat.information, m_chatInformation.data(),
//				m_chatInformation.size());
//		return info;
//	}
};


  void chat_room::join(chat_session_ptr participant) {
		//std::lock_guard<std::mutex> lock(m_mutex);
		m_strand.post([this, participant]{
				participants_.insert(participant);
				for (const auto& msg : recent_msgs_)
				participant->deliver(msg);
				});
  }

  void chat_room::leave(chat_session_ptr participant) {
		//std::lock_guard<std::mutex> lock(m_mutex);
		m_strand.post([this,participant]{
    participants_.erase(participant);});
  }

  void chat_room::deliver(const chat_message &msg) {
		//std::lock_guard<std::mutex> lock(m_mutex);
		m_strand.post([this, msg]{
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

    for (auto& participant : participants_)
      participant->deliver(msg);
		});
  }


//----------------------------------------------------------------------

class chat_server {
public:
  chat_server(boost::asio::io_service &io_service,
              const tcp::endpoint &endpoint)
      : acceptor_(io_service, endpoint), socket_(io_service), room_(io_service) {
    do_accept();
  }

private:
  void do_accept() {
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
      if (!ec) {
        auto session =
            std::make_shared<chat_session>(std::move(socket_), room_);
        session->start();
      }

      do_accept();
    });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
  chat_room room_;
};


static std::function<void()> safeQuit;

void signalHandler(int sig) {
  BOOST_LOG_TRIVIAL(info) << "handle system signal "<<sig;
  if (safeQuit) {
    safeQuit();
    safeQuit = nullptr;
  }
}

//----------------------------------------------------------------------
void init() {
	boost::log::core::get()->set_filter
		(
		 boost::log::trivial::severity >= boost::log::trivial::info
		);
}

int main(int argc, char *argv[]) {
  try {
		GOOGLE_PROTOBUF_VERIFY_VERSION;
		init();
		BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
		BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
		BOOST_LOG_TRIVIAL(info) << "An informational severity message";
		BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
		BOOST_LOG_TRIVIAL(error) << "An error severity message";
		BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
    if (argc < 2) {
      std::cerr << "Usage: chat_server <port> [<port> ...]\n";
      return 1;
    }
		base = std::chrono::system_clock::now();

    boost::asio::io_service io_service;
		safeQuit = [&io_service]{io_service.stop();};
		signal(SIGINT, signalHandler);










    std::list<chat_server> servers;
    for (int i = 1; i < argc; ++i) {
      tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
      servers.emplace_back(io_service, endpoint);
    }

		std::vector<std::thread> threadGroup;
		for(int i = 0; i < 5; ++i) {
			threadGroup.emplace_back([&io_service, i]{
					std::cout << i << " name is " << std::this_thread::get_id() << std::endl;
					io_service.run();});
		}

		BOOST_LOG_TRIVIAL(info) << "main thread name is " << std::this_thread::get_id() << std::endl;
		io_service.run();
		for(auto& v : threadGroup) v.join();
  } catch (std::exception &e) {
		BOOST_LOG_TRIVIAL(error) << "Exception: " << e.what();
    std::cerr << "Exception: " << e.what() << "\n";
  }

	google::protobuf::ShutdownProtobufLibrary();
	BOOST_LOG_TRIVIAL(info) << "safe release all resource";
  return 0;
}
