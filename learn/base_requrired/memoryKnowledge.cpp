/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
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
#include <memory>
static void versionOne();
static void versionTwo();
static void versionThree();

int main(int /* argc */, char** /* argv */) {

	// c++11(包括后续版本) 内存的基本知识
	versionOne();
	versionTwo();
	versionThree();

    //    return EXIT_SUCCESS;
}

const char* getName() {
	static char valueGroup[1000];
	// do some thing
	return valueGroup;
}

const char* getName2() {
	char* value = (char*)malloc(1000);
	// do something
	return value;
}

char* getName(char* v, size_t bufferSize) {
	// do something
	return v;
}

void badThing() {
	throw 1;
}

class SafeIntPointer {
	public:
		explicit SafeIntPointer(int v) : m_value(new int(v)),m_used(1) {}
		~SafeIntPointer() {
			m_used--;
			if (m_used <= 0)
				delete m_value;
		}
		// copy
		// operator =
		int* get() { return m_value;}
	private:
		int m_used;
		int* m_value;
};


void versionOne() {
	//void*
	int* ageC = (int*)malloc(sizeof(int));
	if(ageC) {

	}
	free(agcC);
	char* c = (char*)malloc(100);
	free(c);

  int* age = new int(25);
  int* height = new int(160);

	badThing();

  std::cout << "VersionOne: your age is " << *age << ", and your height is "
            << *height << std::endl;

	// if forget, TOO BAD thing will happen
	// delete [] buffer;
	delete height;
	delete age;
}

void versionTwo() {
	std::shared_ptr<int> age(new int(28));
	std::shared_ptr<int> height(new int(160));

  std::cout << "VersionTwo: your age is " << *age << ", and your height is "
            << *height << std::endl;
	// 不需要做任何额外的事情，内存会自动的释放掉
}

void versionThree() {

	std::shared_ptr<int> age = std::make_shared<int>(35);
	std::shared_ptr<int> height = std::make_shared<int>(160);

  std::cout << "VersionThree: your age is " << *age << ", and your height is "
            << *height << std::endl;
	// 不需要做任何额外的事情，内存会自动的释放掉
	// 并且比第二个版本要好
}

