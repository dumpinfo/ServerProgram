/*
 * =====================================================================================
 *
 *       Filename:  Header.cpp
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
#include "Header.h"

Good::Good(const C& c) { m_cGroup.push_back(c); }
Good::~Good() {}
B Good::handle(int) { return B(); }
C Good::action(int, int) { return C(); }
C& Group::getC(int pos) { return m_cGroup.at(pos); }
E Group::caculate(int) { return E(); }
std::ostream& Group::print(std::ostream& s) const { return s; }

