/*
 * =====================================================================================
 *
 *       Filename:  Parent.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Tuesday, April 26, 2016 08:29:40 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "Parent.h"
#include <cassert>
#include "Child.h"

void Parent::checkParent() {
  for (auto child : m_children) {
    assert(child->getParent() == this);
  }
}

