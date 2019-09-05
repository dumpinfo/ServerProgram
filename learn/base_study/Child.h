/*
 * =====================================================================================
 *
 *       Filename:  Child.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Tuesday, April 26, 2016 08:19:10 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_CHILD_H
#define FND_CHILD_H
class Parent;
class Child {
	public:
		explicit Child(Parent* p) : m_parent(p) {}
		Parent* getParent() { return m_parent;}
	private:
		Parent* m_parent;
};
#endif

