/*
 * =====================================================================================
 *
 *       Filename:  CppLambda.cpp
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
#include <functional>
#include <iostream>

void printInfo(int a, int b, int c) {
	std::cout << "a " << a << "b " << b << "c " << c <<std::endl;
}

struct Print {
	void operator()(int a, int b, int c) const {
		std::cout << "a " << a << "b " << b << "c " << c << std::endl;
	}
};

template<typename T1, typename T2, typename T3>
void templatePrint(T1 a, T2 b, T3 c) {
	std::cout << "a " << a << "b " << b << "c " << c << std::endl;
}

struct TemplatePrint {
	template<typename T1, typename T2, typename T3>
		void operator()(T1 a, T2 b, T3 c) const {
			std::cout << "a " << a << "b " << b << "c " << c << std::endl;
		}
};

inline void print
(int a, int b, int c) {
  std::cout << "a " << a << "b " << b << "c " << c << std::endl;
}

template<typename Func>
void printUseFunc(Func func, int a, int b, int c) {
	func(a,b,c);
}

int main() {
	Print printUseClass;
	TemplatePrint printUseTempClass;

	print(1,2,3);
	printInfo(1,2,3);
	printUseClass(1,2,3);
	templatePrint(1,2,3);
	printUseTempClass(1,2,3);
	int a = 1;
	int b = 2;
	int c = 3;
	// lambda c++
	auto local = [&]
		() {
			std::cout << "a " << a << "b " << b << "c " << c << std::endl;
		};
	local();
}

