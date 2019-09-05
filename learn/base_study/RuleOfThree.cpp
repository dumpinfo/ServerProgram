/*
 * =====================================================================================
 *
 *       Filename:  RuleOfThree.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <vector>
#include <cstdlib>
class RuleOfFive;

std::vector<int> makeVector() {
	std::vector<int> v(100);
	for(int i = 0; i < 100; ++i) v[i] = rand() %100;
	return v;
}

auto v = makeVector();

void leftOrRight() {
	int a = 0;
	int b;
	int c = 2 + 3;
	int d = a + c;
	auto address = &a;
	auto address2 = &(2+3);
	int& e = a;
	int& le = 2;
	int&& re = 2;
}

class RuleOfThree {
  char* cstring;  // raw pointer used as a handle to a dynamically-allocated
                  // memory block
 public:
  RuleOfThree(const char* arg)
      : cstring(new char[std::strlen(arg) + 1])  // allocate
  {
    std::strcpy(cstring, arg);  // populate
  }
  ~RuleOfThree() {
    delete[] cstring;  // deallocate
  }
 private:
  RuleOfThree(const RuleOfThree& other) = delete;  // copy constructor
////  {
////    cstring = new char[std::strlen(other.cstring) + 1];
////    std::strcpy(cstring, other.cstring);
////  }
  RuleOfThree& operator=(const RuleOfThree& other) = delete;  // copy assignment
////  {
////    char* tmp_cstring = new char[std::strlen(other.cstring) + 1];
////    std::strcpy(tmp_cstring, other.cstring);
////    delete[] cstring;
////    cstring = tmp_cstring;
////    return *this;
////  }
};
RuleOfThree rule("this");
RuleOfThree rule2(rule);
