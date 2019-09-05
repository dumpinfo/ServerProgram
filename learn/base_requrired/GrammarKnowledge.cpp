/*
 * =====================================================================================
 *
 *       Filename:  grammarKnowledge.cpp
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
#include <string>
#include <typeinfo>
#include <vector>

static void autoValue();
static void autoPointer();
static void newVersionFor();
static void newVersionConstruct();
static void defaultInitValue();
static void leftRefAndRightRef();

int main(int /* argc  */, char** /* argv */) {

	// new version auto
	//autoValue();
	// autoPointer();
	//newVersionFor();
//	newVersionConstruct();
//	defaultInitValue();
	leftRefAndRightRef();
}

static void autoValue() {
	auto age = 10;
	auto name = std::string("Yt");
	auto height = 160.0f;
	auto weight = 72.0;
	std::cout << "age is type " << typeid(age).name() << std::endl;
	std::cout << "name is type " << typeid(name).name() << std::endl;
	std::cout << "height is type " << typeid(height).name() << std::endl;
	std::cout << "weight is type " << typeid(weight).name() << std::endl;
}

static void autoPointer() {
	auto age = new int(10);
	auto name = "Yt";
	auto height = new float(160.0f);
	auto weight = new double(72.0);

	std::cout << "age is type " << typeid(age).name() << std::endl;
	std::cout << "name is type " << typeid(name).name() << std::endl;
	std::cout << "height is type " << typeid(height).name() << std::endl;
	std::cout << "weight is type " << typeid(weight).name() << std::endl;
}

class MyVector {
	public:
		using GroupType = std::vector<int>;
		//typedef std::vector<int> GroupType;
		//GroupType::iterator begin() { return m_group.begin();}
		//GroupType::iterator end() { return m_group.end();}
	public:
		GroupType m_group;
};

MyVector::GroupType::iterator begin(MyVector& v) {
	return v.m_group.begin();
}

MyVector::GroupType::iterator end(MyVector& v) {
	return v.m_group.end();
}

static void newVersionFor() {
	MyVector vv;
	for(auto v : vv) {

	}
  int ids[] = {1, 2, 3, 4, 5};
  std::cout << "new version ";
  for (auto v : ids) {
    std::cout << v << " ";
  }
  std::cout << std::endl;  // "\n";

  std::cout << "old version ";
  // old version
  for (int i = 0; i < sizeof(ids) / sizeof(int) / 2; ++i) {
    std::cout << ids[i] << " ";
  }
  std::cout << std::endl;  // "\n";

  std::vector<int> group;
  for (int i = 0; i < 4; ++i) group.push_back(i);
  // auto version
	for(std::vector<int>::const_iterator iter = group.begin(), iterEnd = group.end();
			iter != iterEnd; ++iter) {
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	for(size_t i = 0, size = group.size(); i < size; ++i) {
		std::cout << group[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "vector verion : ";
  for (auto v : group) {
		v = v * v;
  }
	std::cout << std::endl;


  for (auto& v : group) {
		v = v * v;
  }

  for (const auto& v : group) {
  }
}

class A {
	public:
		// why explicit?? 具体的含义是什么呢
		explicit A(int value) : m_value(value) {}
	private:
		int m_value;
};

static void newVersionConstruct() {
	int avector[] = { 1, 2, 3};
	std::vector<int> bv = { 1, 2, 3};
  A a(10);
  A b{3};

  A c(true);
  A d{true};

	A e(1.1);
	//A f{1.0};
}

class B {
 public:
  B() : m_age(18), m_height(170), m_weight(75) {}
  explicit B(int age) : m_age(age), m_height(170), m_weight(75) {}
  B(int age, int height)
      : m_age(age), m_height(height) /*, m_height(75) forget bad */ {}
	int age() const { return m_age;}
	int height() const { return m_height;}
	int weight() const { return m_weight;}
 private:
	int m_age;
	int m_height;
	int m_weight;
};

class NewB {
 public:
  NewB() {}
  explicit NewB(int age) : m_age{age} {}
  NewB(int age, int height) : m_age(age), m_height{height} {}
  int age() const { return m_age; }
  int height() const { return m_height; }
  int weight() const { return m_weight; }

 private:
  int m_age = 18;
  int m_height = 170;
  int m_weight = 75;
	int m_value{};
	double m_fightValue{};
};

static void defaultInitValue() {
  B a(10, 20);
  NewB b(10, 20);
  std::cout << "Old b age is " << a.age() << " height " << a.height()
            << " weight " << a.weight() << std::endl;
  std::cout << "New b age is " << b.age() << " height " << b.height()
            << " weight " << b.weight() << std::endl;
}

void printInfo(const int& a) {
	std::cout << a << std::endl;
}

std::vector<int> create(int size) {
	return std::vector<int>(size);
}

static void leftRefAndRightRef() {
  // 什么是引用
  int a = 10;
  int& refA = a;
  const int& constRefA = a;

  std::cout << " a " << a << " ref of a " << refA << " const ref a "
            << constRefA << std::endl;

	// this is a error
	//int& refB = 10;
  const int& constRefB = 10;
	printInfo(constRefB);
	printInfo(10);
	printInfo(a);
	printInfo(refA);
  std::cout << "different version const ref " << constRefB << std::endl;

	auto&& rrA = 10;
	int&& rrB = 20;
	const int&& crrB = 20;
	rrA = 30;
  std::cout << " right ref of b " << rrB << " const right ref b "
            << crrB << std::endl;

	int b = 20;
	// error why?
	//int&& rrB = b;
	//const int&& crrB = b;
	int&& newRRB = std::move(b);
	const int&& cNewRRB = std::move(b);
  std::cout << " b " << b << " right ref of b " << newRRB<< " const right ref b "
            << cNewRRB << std::endl;
	std::cout << "address " << &b << " ref " << &newRRB << " c ref " << &cNewRRB << std::endl;
}


