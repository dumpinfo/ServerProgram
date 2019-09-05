/*
 * =====================================================================================
 *
 *       Filename:  Parent.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Tuesday, April 26, 2016 08:17:42 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_PARENT_H
#define FND_PARENT_H
#include <vector>
class Child;
class Parent {
public:
  void addChild(Child *child) {
    m_children.push_back(child);
  }
	void checkParent();
private:
  std::vector<Child *> m_children;
};
#endif
