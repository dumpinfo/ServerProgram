/*
 * =====================================================================================
 *
 *       Filename:  Logic.cpp
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
#include "OO.h"
#include "Event.h"

int main() {

  Drived *info = new Drived(1);
	Grouped *group = new Grouped(2);
	Event ev;

	group->print();
	group->act(ev);
	group->addBase(info);
	group->removeBase(info->id());
	group->id();

	Base* baseGroup = group;
	baseGroup->act(ev);
	baseGroup->print();
	baseGroup->id();
	baseGroup->addBase(info);
	baseGroup->removeBase(info->id());

	//delete group;
	delete baseGroup;
  delete info;
}

