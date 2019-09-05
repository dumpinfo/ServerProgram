/*
 * =====================================================================================
 *
 *       Filename:  ClassVirtual11.cpp
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
#include <iostream>
namespace TestA {
class B {
  virtual void do_f(){};  // private member
 public:
  void f() { do_f(); };  // public interface
virtual ~B() {}
};
struct D : public B {
  void do_f() override {}  // overrides B::do_f
};
}
namespace TestB {

struct V {
  virtual void f() { std::cout << "V::f\n";}
  virtual void g() { std::cout << "V::g\n";}
};

struct A : virtual V {
  virtual void f() {std::cout << "A::f\n";}  // A::f is the final overrider of V::f in A
};
struct B : virtual V {
  virtual void g() { std::cout << "B::g\n";}  // B::g is the final overrider of V::g in B
  B(V*, A*);
};
struct D : A, B {
  virtual void f() { std::cout << "D::f\n";}  // D::f is the final overrider of V::f in D
  virtual void g() { std::cout << "D::g\n";}  // D::g is the final overrider of V::g in D

  // note: A is initialized before B
  D() : B((A*)this, this) {}
};

// the constructor of B, called from the constructor of D
B::B(V* v, A* a) {
  f();  // virtual call to V::f (although D has the final overrider, D doesn't
        // exist)
  g();  // virtual call to B::g, which is the final overrider in B

  v->g();  // v's type V is base of B, virtual call calls B::g as before

  a->f();  // a’s type A is not a base of B. it belongs to a different branch of
           // the
  // hierarchy. Attempting a virtual call through that branch causes
  // undefined behavior even though A was already fully constructed in this
  // case (it was constructed before B since it appears before B in the list
  // of the bases of D). In practice, the virtual call to A::f will be
  // attempted using B's virtual member function table, since that's what
  // is active during B's construction)
}
}

int main(int, char**) {
  TestA::D d;
  TestA::B* bp = &d;
  bp->f();  // calls D::do_f();

	TestB::D dd;
}
