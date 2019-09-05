/*
 * =====================================================================================
 *
 *       Filename:  PureVirtualDesc.cpp
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

struct A {
	virtual ~A() = 0; // WHY??????
};
A::~A() {}

struct B : A {};

int main(int,char**) {
	B b;
}

