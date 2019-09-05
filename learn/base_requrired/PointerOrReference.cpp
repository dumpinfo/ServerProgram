/*
 * =====================================================================================
 *
 *       Filename:  PointerOrReference.cpp
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
int usePointer(int* a) {
	std::cout << "p " << *a << std::endl;
}

int useReference(int& a) {
	std::cout << "r " << a << std::endl;
}

int main(int argc, char** argv) {
	int a = 0;
	usePointer(&a);
	useReference(a);
}

