/*
 * =====================================================================================
 *
 *       Filename:  ClassKnowledge.cpp
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
#include <complex>
#include <iostream>

// 编译器为我们实现了几个类成员函数?
class Empty {};

// 编译器为我们实现了几个类成员函数？
class AnotherEmpty : public Empty {};

// 编译器为我们实现了几个类成员函数？
class Void {
	public:
		Void() {}
};

// 编译器为我们实现了几个类成员函数？
class NotEmpty {
	public:
		NotEmpty(int a) : m_value(a) {}
	private:
		int m_value;
};





// why not safe???
class NotSafe {
	public:
		NotSafe(int v) : m_value(new int(v)) {}
		~NotSafe() { if(m_value) delete m_value;}
	private:
		int* m_value;
};

class Base {
	public:
		virtual void handle(int);
		virtual void handle(double);
		virtual void deal(int = 10);
};

void Base::handle(int) {
	std::cout << "Base::handle(int)\n";
}

void Base::handle(double) {
	std::cout << "Base::handle(double)\n";
}

void Base::deal(int v) {
	std::cout << "Base::deal " << v << std::endl;
}

// public继承到底是什么意思呢?
class Derived : public Base {
	public:
		void handle(std::complex<double>);
		void deal(int v = 20);
};

void Derived::handle(std::complex<double>) {
	std::cout << "Derived::handle(std::complex)\n";
}

void Derived::deal(int v) {
	std::cout << "Derived::deal " << v << std::endl;
}

void testBaseAndDerived() {
  Base b;
  Derived d;
	// C++ 的多态是怎么实现的?
  Base* pb = new Derived;
  b.handle(1.0);
  d.handle(1.0);
  pb->handle(1.0);
  b.deal();
  d.deal();
  pb->deal();
  delete pb;
}

template<typename T>
class GoodObject {
 public:
  int size() const { return m_size; }
  void handle(T obj) {
    // do many many work
  }
	GoodObject(int s) : m_size(s) {}
 private:
	int m_size;
	T m_object;
};

template <typename T>
class BetterObjectOne : private GoodObject<T> {
 public:
  BetterObjectOne(int s) : GoodObject<T>(s) {}
  void deal(T obj) { handle(obj); }
  // we use size atomatic ?????
	using GoodObject<T>::size;
};

template <typename T>
class BetterObjectTwo {
 public:
  void deal(T obj) { m_object.deal(obj); }
  int size() const { return m_object.size(); }
  BetterObjectTwo(int s) : m_object(s) {}

 private:
  GoodObject<T> m_object;
};

static void whichOneDoYouLike() {
	BetterObjectTwo<int> me(10);
	std::cout << me.size() << std::endl;
	BetterObjectOne<int> you(10);
	std::cout << you.size() << std::endl;
}


class ObjectA {
 public:
  explicit ObjectA(int a) : m_value(new int(a)) {}
  ~ObjectA() { delete m_value; }

 private:
  int* m_value;
};

class Evil {
 public:
  Evil() { throw 10; }
  ~Evil() {}
};

class Normal : public ObjectA {
 public:
  explicit Normal(int a) : ObjectA(a), m_a(a + 1), m_resource(new int(a + 2)) ,m_evil(){}
  ~Normal() { delete m_resource; }

 private:
  ObjectA m_a;
  int* m_resource;
  Evil m_evil;
};



static void hasMemoryLeak() {
  try {
    Normal n(1);
  } catch (...) {
  }
}









class TestObject {
 public:
  TestObject(int a) : m_value(a) {}
  TestObject(const TestObject& rhs) : m_value(rhs.m_value) {}

 private:
  int m_value;
};

static void hasDifference() {
	TestObject a(2);
	TestObject d = 2;

	TestObject b(a);
	TestObject c = a;
}










int main(int argc, char** argv) {
	//testBaseAndDerived();
	//whichOneDoYouLike();
	// has memory leak ? why ????
	hasMemoryLeak();
	hasDifference();
}















void isGoodOrBad(std::vector<int>& objects) {
	// objects is very huge
	// we only need top ten
	std::sort(objects.begin(), objects.end());
	if(objects.size() > 10) objects.erase(objects.begin() + 10, objects.end());
}








