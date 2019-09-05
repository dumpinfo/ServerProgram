/*
 * =====================================================================================
 *
 *       Filename:  RuleOfFive.cpp
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
class RuleOfFive {
  char* cstring;  // raw pointer used as a handle to a dynamically-allocated
                  // memory block
 public:
  RuleOfFive(const char* arg)
      : cstring(new char[std::strlen(arg) + 1])  // allocate
  {
    std::strcpy(cstring, arg);  // populate
  }
  ~RuleOfFive() {
    delete[] cstring;  // deallocate
  }
  RuleOfFive(const RuleOfFive& other)  // copy constructor
  {
    cstring = new char[std::strlen(other.cstring) + 1];
    std::strcpy(cstring, other.cstring);
  }
  RuleOfFive(RuleOfFive&& other)
      : cstring(other.cstring)  // move constructor
  {
    other.cstring = nullptr;
  }
  RuleOfFive& operator=(const RuleOfFive& other)  // copy assignment
  {
    char* tmp_cstring = new char[std::strlen(other.cstring) + 1];
    std::strcpy(tmp_cstring, other.cstring);
    delete[] cstring;
    cstring = tmp_cstring;
    return *this;
  }
  RuleOfFive& operator=(RuleOfFive&& other)  // move assignment
  {
    delete[] cstring;
    cstring = other.cstring;
    other.cstring = nullptr;
    return *this;
  }
  // alternatively, replace both assignment operators with
  //  RuleOfFive& operator=(RuleOfFive other)
  //  {
  //      std::swap(cstring, other.cstring);
  //      return *this;
  //  }
};

class RuleOfZero{
  std::string cppstring;

 public:
  RuleOfZero(const std::string& arg) : cppstring(arg) {}
};
