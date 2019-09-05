/*
 * =====================================================================================
 *
 *       Filename:  TemplateAndTraits.cpp
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
#include <string>
#include <iostream>
#include <type_traits>
struct A {
	int a;
};

struct B :A {
	int b;
};













class Object {
	public:
		Object() : m_value(new int(4)) {}
		~Object() {delete m_value;}
	private:
		int m_data[100];
		int * m_value;
};

char info[10000];
void placementNew() {
	Object* s = new(info)Object();
	// right?
	//s->~Object();
	// or
	delete s;
	std::vector<Object> a;
	a.reserve(100);
	a.push_back(Object());
	a.pop_back();
}













template<typename T>
struct EmptyHelper : T {
	int group[256];
};

struct EmptyHelper2 {
	int group[256];
};

template <typename T>
bool isEmptyClass() {
  return sizeof(EmptyHelper2) == sizeof(EmptyHelper<T>);
}



struct Empty {

};


struct DummyEmpty {
	char a;
};


static void testEmptyClass() {
	std::cout << "Empty is " << sizeof(Empty) << std::endl;
	std::cout << "DummyEmpty is " << sizeof(DummyEmpty) << std::endl;
	std::cout << "Empty is " << isEmptyClass<Empty>() << std::endl;
	std::cout << "DummyEmpty is " << isEmptyClass<DummyEmpty>() << std::endl;

}










void standardLayout() {
	std::cout << "int is " << std::is_standard_layout<int>::value << std::endl;
	std::cout << "A is " << std::is_standard_layout<A>::value << std::endl;
	std::cout << "B is " << std::is_standard_layout<B>::value << std::endl;
}

int main(int /*argc*/, char** /* argv */) {
	//placementNew();
	testEmptyClass();
}

