/*
 * =====================================================================================
 *
 *       Filename:  CppKeywords.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt(fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>
/* key words of cpp
 * alignas （C++11 起）
 * alignof （C++11 起）
 * and
 * and_eq
 * asm
 * auto
 * bitand
 * bitor
 * bool
 * break
 * case
 * catch
 * char == unsigned char linux signed char
 * char16_t（C++11 起）Unicode utf8
 * char32_t（C++11 起）Unicode
 * class
 * compl ~
 * concept （概念TS）
 * const   multithread
 * constexpr（C++11 起）
 * const_cast
 * continue
 * decltype（C++11 起）
 * default (normal use        speical use)
 * delete
 * do
 * double
 * dynamic_cast
 * else
 * enum
 * explicit
 * export
 * extern
 * false
 * float
 * for
 * friend
 * goto
 * if
 * inline
 * int signed
 * long
 * mutable
 * namespace
 * new
 * noexcept（C++11 起）
 * not !
 * not_eq !=
 * nullptr （C++11 起）
 * operator + - ||
 * or ||
 * or_eq |=
 * private
 * protected
 * public
 * register
 * reinterpret_cast
 * requires（概念TS）
 * return
 * short
 * signed
 * sizeof
 * static
 * static_assert（C++11 起）
 * static_cast
 * struct
 * switch
 * template
 * this
 * thread_local（C++11 起）
 * throw
 * true
 * try
 * typedef
 * typeid
 * typename
 * union
 * unsigned
 * using
 * virtual
 * void
 * volatile
 * wchar_t
 * while
 * xor ^
 * xor_eq ^=
 * */








/* aggregate initialization */
void aggregateInit() {
	char a[]= "abc";
	//char b[5]{"abc"};
	//wchar_t c[] = {L"abc"};
}

int f(bool b) {
  int x;                // OK: the value of x is indeterminate
  int y = x;            // undefined behavior
	std::cout << "x y " << x << " " << y << std::endl;
  unsigned char c;      // OK: the value of c is indeterminate
  unsigned char d = c;  // OK: the value of d is indeterminate
  std::cout << "c d " << static_cast<int>(c) << " " << static_cast<int>(d)
            << std::endl;
  int e = d;            // undefined behavior
  return b ? d : 0;     // undefined behavior if b is true
}









struct A {
  int i;
  A() {}  // user-provided default ctor, does not initialize i
};

struct B {
  A a;
};  // implicitly-defined default ctor

void testB() {
std::cout << B().a.i << '\n';
A a;
int c;
std::cout << "a.i " << a.i  << "c " << c << std::endl;
int* pa = new int;
int* pb = new int();
std::cout << "pa pb" << *pa << " " << *pb << std::endl;
delete pa;
delete pb;
}

void doSomething(bool isGood, bool isHero, bool isMom) {
	if(isGood) {

	} else {

	}

	// ....
}

void testBool() {
	int a = 10;
	for(;;) {
		for(;;) {
			++a;
			if(a % 2 == 0) continue;
			if(a > 1000) break;
		}

		if(a > 100000) break;
	}
}

int fact(int n) {
	return n < 1? 1: (n * fact(n-1));
}

constexpr int factorial(int n) { return n <= 1 ? 1 : (n * factorial(n - 1)); }

template<int N>
struct NN {
	void print() { std::cout << N << std::endl;}
};

void testA(const int& a) {

}

void testB(const int& b) {

}

void testConstCast() {
	const int j = 3; // j is declared const
	std::thread aa([&j]{testA(j);});
	std::thread bb([&j]{testB(j);});
	//const int*
	int* pj = const_cast<int*>(&j);
	*pj = 4;         // undefined behavior!
}

struct A { double x; };
void testDecl() {
	const A* a = new A{0};
	auto aa = a->x;
	auto y = a->x;
	decltype(a->x) y;       // double
	auto& cc = y;
	decltype((a->x)) z = y; // double&
}







template<typename T, typename U>
auto add(T a, U b) {
	auto c = a+ b;
	return c;
	return (c);
}

struct Base{virtual ~Base(){}};

struct Derived : Base {
  virtual void name() {}
};

void testDyn() {
  Base *b1 = new Base;
  if (Derived *d = dynamic_cast<Derived *>(b1)) {
    std::cout << "downcast from b1 to d successful\n";
    d->name(); // safe to call
  }
	// static_cast

  Base *b2 = new Derived;
  if (Derived *d = dynamic_cast<Derived *>(b2)) {
    std::cout << "downcast from b2 to d successful\n";
    d->name(); // safe to call
  }
	Base bb;
	Derived& cc = dynamic_cast<Derived&>(bb);
}

struct A {
  A(int) {}
  A(int, int) {}
  operator int() const { return 0; }
};

struct B {
  explicit B(int) {}
  explicit B(int, int) {}
  explicit operator int() const { return 0; }
};

void handleA(A a) {

}

void handleB(B b) {

}

void testS(const std::string& s) {

}

void testExpl() {
	A a1 = 1; // A a1 = A(1);
	// B b1 = 1; //
	A a2(2);
	B b2(2); // OK
	A a3 = {4, 5}; // A a3 = A(4,5); A{4,5};
	//B b3 = {4,5}; //
	int na1 = a1; // OK
	//int nb1 = b2; // BAD
	int na2 = static_cast<int>(a1);
	int nb2 = static_cast<int>(b2);
	A a4 = (A)1;
	B b4 = (B)1;

	handleA(a1);
	handleA(1);
	handleB(b2);
	//handleB(2);
	std::string s("ok");
	testS(s);
	testS("ok");

}

enum Color { red = 255, green, blue = red + green };

void testOldEnum() {
  Color r = red;
  switch (r) {
  case red:
    std::cout << "i'm red\n";
    break;
  case green:
    std::cout << "i'm green\n";
    break;
  case blue:
    std::cout << "i'm blue\n";
    break;
  default:
    std::cout << "what?\n";
  }
	int a = r;
}

enum class IsGood {
	Yes,
	No
};
enum class IsHero {
	Yes,
	No
};
enum class IsMom{
	Yes,
	No
};

void show(IsGood, IsHero, IsMom) {

}

void show(bool isGood, bool isHero, bool isMom) {
	
}

void test() {
	show(true, false, false);
	show(IsGood::Yes, IsHero::No, IsMom::No);
}

enum class NewColor : long long { Red, Green = 20, Blue };
void testNewEnum() {
  NewColor r = NewColor::Blue;
  switch (r) {
  case NewColor::Red:
    std::cout << "red\n";
    break;
  case NewColor::Green:
    std::cout << "green\n";
    break;
  case NewColor::Blue:
    std::cout << "blue\n";
    break;
  }
	int a = static_cast<int>(r);
}

class Y {
  int data; // private member
  friend std::ostream &operator<<(std::ostream &out, const Y &o);
  template <typename T> friend class B; // every B<T> is a friend of Y

  template <typename T> friend void f(T) {} // every f<T> is a friend of Y
};

class YY : public Y {

};

std::ostream &operator<<(std::ostream &out, const Y &y) {
  return out << y.data;
}

void testGoto() {
	auto i = 0;
label:
	std::cout << "hello\n";
	for (; i < 10; i++) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				if (i == 3) {
					++i;
					goto label;
				}
				if (i == 8)
					goto endloop;
			}
		}
	}
endloop:
	std::cout << "good bye\n";
}

inline int add(int a, int b) {
	return a + b;
}

template<typename T>
void print(T const& t) {
	t.print();
}

class In {
	public:
		void print() const { std::cout << "hello\n";}
		int value() const { return m_value;}
	private:
		int m_value;

};

namespace {
	std::string astring("long");
}

static std::string astring;

namespace XGroup {
	class A {
		int value;
	};
}

namespace YGroup {
	class A {
		int value;
	};
	class B {

	};
}

class A {
	int value;
	A() { throw 1;}
};

void testNamespace() {
	XGroup::A a;
	YGroup::A b;
	A c;
}

void testNamespace2() {
	namespace CGroup = XGroup;
	CGroup::A a;
	using YGroup::B;
	B b;
	YGroup::A aa;
	using namespace YGroup;
	A c;
}

void f() noexcept(false) {
}

template<typename T, typename U>
void func(T t, U u) {
	t(u);
}

void nullPointer(int* a) {
	std::cout << "i'm a pointer\n";
}

struct AAA {
	~AAA() { delete m_value;}
	AAA() : m_value(new int()) {}
	AAA(const AAA& rhs) : m_value(new int(*(rhs.m_value))) {}
	AAA& operator = (const AAA& rhs) {
		*m_value = *(rhs.m_value);
		return *this;
	}
	// = == < >= > <= !=
	// +
	// +=
	private:
		int* m_value;
};

void testOperator() {
	std::string a("abc");
	std::string b("cde");
	auto c = a + b;
	c += a;
}

void testNullPointer() {
	nullPointer(0);
	nullPointer(NULL); // (void*)0 c / 0
	nullPointer(nullptr);
	func(nullPointer, nullptr);
	func(nullPointer, (int*)0);
	func(nullPointer, NULL);

}

void testReinter() {
	int a = 1;
	auto p = reinterpret_cast<char*>(&a);
	if(p[0] == 1) std::cout << "the system is little endian\n";
	else std::cout << "the system is big endian\n";
	// reinterpret_cast
	// static_cast
	// const_cast
	// dynamic_cast
	// c like cast
	auto pp = (char*)(&a);
	const AAA bb;
	auto pbb = const_cast<AAA*>(&bb);
	auto cbb = (AAA*)(&bb);
	int c = 100;
	auto cc = static_cast<char>(c);
	auto ccc = (char)c;
}


struct Empty {};
struct Base { int a; };
struct Derived : Base { int b; };
struct Bit { unsigned bit: 1; };
// c++11 before
void testSizeof() {
	Empty e;
	Derived d;
	Base& b = d;
	Bit bit;
	std::cout << 1 << std::endl;
	std::cout << sizeof(Empty) << std::endl;
	std::cout << sizeof(&e) << std::endl;
	std::cout << sizeof(Derived) << std::endl;
	//std::cout << sizeof(void) << std::endl;
	//std::cout << sizeof(int[]) << std::endl;
	//std::cout << sizeof(bit.bit) << std::endl;
}

struct S {
	static int s;
};
// sizeof(S) == 1

int S::s = 10;

struct Foo;

struct SS {
	static int a[];
	static Foo foo;
	static SS ss;
};

int SS::a[10];
struct Foo {};
Foo SS::foo;
SS SS::ss;

static int globalA = 0;
void printInfo() {
	static int localStatic = 0;
	++localStatic;
	std::cout << S::s << " " << globalA << " " << localStatic << std::endl;
}

void testStaticAssert() {
	int a = 4;
	int b == 5;
  assert((a == b) &&  "only work for int for 32 bit");
}

template<typename T>
void func(T t) {
	static_assert(alignof(T) == 4, "only for alignof 4");
}
typedef unsigned long ulong;
class Comp {
	using Group = std::map<int,ulong>;
//	typedef std::map<int,ulong> Group;
	Group a;
	void aa() {
		//std::map<int, ulong>::iterator iter = a.find(10);
		//Group::iteator iter = a.find(10);
		auto iter = a.find(10);
	}
};

int main(int argc,char**argv) {
	auto cc = add(1.0, 3);
	if(argc > 1) factorial(atoi(argv[1]));
	auto aa = fact(4);
	auto bb = 24; //  factorial(4); // 4 * 3 * 2
	char group[factorial(6)];
	NN<factorial(8)> nn; // 8! 40320
	nn.print();
	// char group2[fact(6)];
}
