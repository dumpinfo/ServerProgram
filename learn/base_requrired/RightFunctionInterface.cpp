/*
 * =====================================================================================
 *
 *       Filename:  RightFunctionInterface.cpp
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
#include <vector>
// 当我们声明了一个class,实际上声明了几个类函数？？
class Object {
};


// C++98 vesion
class Object2 {
	public:
		Object2() {}
		/* inline  */ ~Object2() {}
		Object2(const Object2&) {}
		Object2& operator = (const Object2&) {}
};

static void printObject(const Object&) {}


class Object3 {
	public:
		virtual ~Object3() {}
		int print() {}
};

// has error
class Person {
	public:
		Person() : m_id(++c_personId) {}
		virtual void print() {}
		int id() const { return m_id;}
		Person(const Person& p) : m_id(p.id()) {}
	private:
		int m_id;
		static int c_personId;
};

int Person::c_personId = 0;

class Student : public Person {
	public:
		virtual void print() {std::cout << "i'm a student id is " << id()<< "\n";}
};

class Teacher : public Person {
	public:
		virtual void print() {std::cout << "i'm a teacher id is " << id() << "\n";}
};

// what are you want doing????
class Me : public Student, public Teacher {
};

class Monster : virtual public Person {
	public:
		virtual void print() { std::cout << "i'm a monster id is " << id() << "\n";}
};

class Angle : virtual public Person {
	public:
		virtual void print() { std::cout << "i'm a angle id is " << id() << "\n";}
};

class You : public Monster, public Angle {
 public:
  virtual void print() {
    std::cout << "i'm angle and monster id is " << id() << "\n";
  }
};

static void groupPerson() {
	std::vector<Person> persons;
	persons.push_back(Person());
	persons.push_back(Student());
	persons.push_back(Teacher());
	//persons.push_back(Me());

	// has a warning why???
	for(int i = 0; i < persons.size(); ++i) {
		persons[i].print();
	}


	std::vector<Person*> pGroups;
	pGroups.push_back(new Person());
	pGroups.push_back(new Student());
	pGroups.push_back(new Teacher());
	//pGroups.push_back(new Me());

	// has a warning why???
	for(int i = 0; i < pGroups.size(); ++i) {
		pGroups[i]->print();
	}

	// memeory leak ???? yes or no? why???
	for(int i = 0; i < pGroups.size(); ++i) {
		delete pGroups[i];
	}
}

class Good {
 public:
  void setHide(bool v) { m_isHide = v; }
	void fillBuffer(std::vector<char>& buffer) {
		if(m_isHide) buffer.push_back('a');
	}
	void fillBuffer(const std::string& s, std::vector<char>& buffer) {
		if(m_isHide) buffer.insert(buffer.end(), s.begin(), s.end());
	}

	void fillBuffer(std::vector<char>& buffer, const std::string& s) {
		if(m_isHide) buffer.insert(buffer.end(), s.begin(), s.end());
	}

	bool& isHide() { return m_isHide;}
	// better ?
	const bool& isHide() const { return m_isHide;}

	//name which is better???
	std::string name() const { return m_name;}
	const std::string& getName() const { return m_name;}
	// in c++11 we have perfect solution
	//
	// never throw in destruct, why???
	~Good() {
		if(!m_isHide) {
			throw std::runtime_error("bad");
		}
	}



 private:
  bool m_isHide;
	std::string m_name;
};







static int callFirst(int a) {
	std::cout << "callFirst "  << a << "\n";
	return ++a;
}

static int callSecond(int a) {
	std::cout << "callSecond "<< a << "\n";
	return --a;
}


static void print(int a, int b) {
	std::cout << "a " << a <<  " b " << b << std::endl;
}




class A {/*   */ };
class B {/* */};
void print(A* a, B* b) {
	try {
//		return;
	// do some
	}catch(...) {
	}

	delete a;
	delete b;
}

void whoCallFirst() {
	try {
		auto a = new A();
		auto b = new B();
	print(a , b);
	} catch(...) {

	}
}





static void testYouAndMe() {

	Me me;
	me.Teacher::print();
	me.Student::print();

	You you;
	you.Angle::print();
	you.Monster::print();
	you.print();
}


template<typename T>
void handle(T* lhs, T* rhs) {
	// never throw exception in this function
	assert(lhs);
	assert(rhs);
	// this fucntion is the owner of this two pointer
	// do thing with lhs rhs
	// .,.........
	delete lhs;
	delete rhs;
}

template<typename T>
void testHandle() {
	handle(new T(), new T());
}

void hasMemoryLeak() {

}

int main(int argc, char** argv) {
	// testYouAndMe
	whoCallFirst();

	// is this exception safe?
	isThisExcetpionSafe();
}



