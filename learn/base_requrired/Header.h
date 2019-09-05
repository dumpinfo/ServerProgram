/*
 * =====================================================================================
 *
 *       Filename:  Header.h
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *   Organization:
 *
 * =====================================================================================
 */
// what's the meaning of this ifndef and define
#ifndef FND_YT_HEADER_H
#define FND_YT_HEADER_H
#include <iostream>
#include <vector>
#include "A.h" // has class A
#include "B.h" // has class B
#include "C.h" // has class C
#include "D.h" // has class D
//#include "E.h" // has class E
//class A;
//class C;
class E;

class Good : public A, private B {
	public:
		Good(const C&);
		~Good();
		B handle(int);
		C action(int, int);
		C& getC(int);
		E caculate(int);
		virtual std::ostream& print(std::ostream& s) const; // came from A
	private:
		std::vector<C> m_cGroup;
		D m_dObject;
};




#endif

