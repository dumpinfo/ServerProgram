/*
 * =====================================================================================
 *
 *       Filename:  LogQuest.cpp
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
#include <stdlib.h>
#include <fstream>
class Log {
	public:
	Log(int id, const std::string& filename) : m_id(id) {
		m_f.open(filename.c_str(), std::fstream::out);
	}
	~Log() {
		// m_f.close();
	}
	void log(const std::string& info) {
		std::cout << info;
		m_f << info;
		m_f.flush();
	}
	private:
	int m_id;
	std::fstream m_f;
};

void test() {
	static Log log(1, "log.log");
	log.log("hello ");
}

void test2() {
	static Log log(2, "log.log");
	log.log("world");
}

int main() {
	test();
	test2();
	// answer
	// hello
	// world
	// hello world
	// worldhello
	//
	std::cout << "bye main thread" << std::endl;
}

