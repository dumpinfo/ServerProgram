/*
 * =====================================================================================
 *
 *       Filename:  Move.cpp
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
#include <cassert>
#include <iostream>
#include <vector>
class RuleOfFive {
public:
  RuleOfFive(const RuleOfFive &rhs) : m_value(new int(*(rhs.m_value))) {}
	RuleOfFive(RuleOfFive&& rhs) = delete;
  RuleOfFive &operator=(const RuleOfFive &rhs) {
    *m_value = *(rhs.m_value);
    return *this;
  }
	RuleOfFive& operator=(RuleOfFive&& rhs) = delete;
  ~RuleOfFive() { delete m_value; }
  RuleOfFive() : m_value(new int(10)) {}
	void print() const {
		//assert(m_value);
		if(m_value)
		std::cout << *m_value << std::endl;
	}

private:
  int *m_value;
};

//RuleOfFive::RuleOfFive(RuleOfFive&& rhs) {
//	m_value = rhs.m_value;
//	rhs.m_value = nullptr;
//}

int print(const int& a) {
	std::cout << a << std::endl;
}
int main() {
	int abc = 10;
	const int& bc = abc;
	print(abc);
	print(bc);
	print(10);

	// && and move
	std::vector<int> a;
	for(int i = 0; i < 10; ++i) a.push_back(i);
	RuleOfFive b;
	auto& c = b;
	// RuleOfFive&&
	RuleOfFive e = b;
	RuleOfFive d = std::move(b);
	e = std::move(e);
	//b.print();
}

