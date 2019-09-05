/*
 * =====================================================================================
 *
 *       Filename:  ClassVirtual.cpp
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
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct BaseBase {
	virtual ~BaseBase() {}
	int value;
	int key;
	void print() const;
	virtual void act() = 0;
	virtual void findIt(int i) { }
};

void testBaseBase(const BaseBase& b) {
	b.value;
	b.key;
	b.print();
}


struct Base {
  virtual void f() { std::cout << "base\n"; }
	virtual ~Base() {
	}
	virtual void init() {}
	Base() {
	}
	protected:
	~Base() {}
};

struct Derived : Base {
  void f() override {  // 'override' is optional
    std::cout << "derived " << m_group.size() <<  "\n";
  }
	void g() {
		std::cout << "g\n";
	}
	void init() override { m_group.resize(1000);}
	private:
	std::vector<int> m_group;
};

void testInfo(const Base& b) {
	b.f();
}

void testBase() {
	Derived d;
	testInfo(d);
	Derived* dp = new Derived();
	delete dp;
}

struct DD : Base {
	public:
		void f() {
		}
		void init() {}
};

int main() {
	auto b = factoryBase(1);
}
//
//  // virtual function call through reference
//  Base& br = b;  // the type of br is Base&
//  Base& dr = d;  // the type of dr is Base& as  well
//  br.f();        // prints "base"
//  dr.f();        // prints "derived"
//
//  // virtual function call through pointer
//  Base* bp = &b;  // the type of bp is Base*
//  Base* dp = &d;  // the type of dp is Base* as  well
//  bp->f();        // prints "base"
//  dp->f();        // prints "derived"
//
//  // non-virtual function call
//  br.Base::f();  // prints "base"
//  dr.Base::f();  // prints "base"
//}
