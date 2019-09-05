/*
 * =====================================================================================
 *
 *       Filename:  BaseCPPTest.cpp
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
#include <cstdlib>
#include <iostream>
//#include <vector>
//#include <map>
//#include <string>
//class BigObject {
//	public:
//		virtual int type() const { return 0;}
//		// has another error do you find it?
//	private:
//		std::vector<int> m_group;
//		std::string m_name;
//};
//
//class BiggerObject : public BigObject {
//	public:
//		/* explicit */BiggerObject(int t) : m_type(t) {}
//		int type() const { return m_type;}
//	private:
//		int m_type;
//
//};
//static void printBigObject(BigObject obj) {
//	// do print info
//}
//
//// interface error ??
//static void handleObject(BigObject* obj) {
//	// do something for obj
//}
//static void printGroup() {
//	// slow version why???
//  std::vector<int> group;
//  for (int i = 0; i < 10; ++i) group.push_back(i);
//  for (std::vector<int>::iterator iter = group.begin(); iter != group.end();
//       iter++) {
//    std::cout << *iter << std::endl;
//  }
//  std::cout << std::endl;
//
//  // slow version why???
//  std::map<int, std::string> idName;
//  idName[10] = "One";
//  idName[11] = "Two";
//  for (std::map<int, std::string>::iterator iter = idName.begin();
//       iter != idName.end(); ++iter) {
//    const std::pair<int, std::string>& value = (*iter);
//    std::cout << value.first << " name " << value.second;
//  }
//  std::cout << std::endl;
//
//}
//
//static void classObject() {
//	// slow version why???
//	BigObject obj;
//	printBigObject(obj);
//	BiggerObject bigger(10);
//	printBigObject(bigger);
//
//	std::vector<BigObject*> objectGroup;
//	objectGroup.push_back(new BigObject());
//	objectGroup.push_back(new BiggerObject(1));
//
//	// have something wrong?? why??
//	for(int i = 0; i < objectGroup.size(); ++i) {
//		handleObject(objectGroup[i]);
//	}
//
//	// don't forget delete object when you dont use
//	// but has a error, do you find it???
//	for(int i = 0; i < objectGroup.size(); ++i) {
//		delete objectGroup[i];
//	}
//}


class A {};
class B { char m_data;};
class C {
	char m_data[100];
};
class D {
	char* m_data;
	D() : m_data(new char[100]) {}
	~D() { delete [] m_data;}
};

static void testSizeof() {
	std::cout << "bool sizeof " << sizeof(bool) << std::endl; // 1
	std::cout << "char sizeof " << sizeof(char) << std::endl; // 1
	std::cout << "int sizeof " << sizeof(int) << std::endl; // 4
	char data[10];
	char* pData = data;
	std::cout << "char data[10] sizeof " << sizeof(data) << std::endl; // 10
	std::cout << "char* sizeof " << sizeof(pData) << std::endl; // 4 8
	std::cout << "A sizeof " << sizeof(A) << std::endl; // 1
	std::cout << "B sizeof " << sizeof(B) << std::endl; // 1
	std::cout << "C sizeof " << sizeof(C) << std::endl; // 100
	std::cout << "D sizeof " << sizeof(D) << std::endl; // 8
	std::cout << "size_t sizeof " << sizeof(std::size_t) << std::endl; // 8
}

static void unsignedAndSigned() {
  std::size_t a = 10;
  int b = -1;
  if (b < a)
    std::cout << "right\n";
  else
    std::cout << "bad\n";
}














static void printAddress(int a ,int b, int c) {
	std::cout << "a " << a << " " << &a << std::endl;
	std::cout << "b " << b << std::endl;
	std::cout << "c " << c << " " << &c << std::endl;
}







namespace A {
  struct X {};
  struct Y {};
  void f(int) {}
  void g(X) {}
}

namespace B {
void f(int i) {
  f(i);
}
void g(A::X x) {
  g(x);
}
void h(A::Y y) {
  h(y);
}
}

namespace C {
	void func(A::X x) {
		g(x);
	}
}










void testADL() {

	std::cout << "hello world";
	endl(std::cout);
}


int main(int argc, char** argv) {
	unsignedAndSigned();
	testSizeof();
	printAddress(1,std::atoi(argv[1]),3);
	testADL();
	//unsignedAndSigned();
	//testSizeof();
	//printAddress(1,std::atoi(argv[1]),3);
//	printGroup();
//	classObject();
}

