/*
 * =====================================================================================
 *
 *       Filename:  OO.h
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
#ifndef FND_CPP_OO_H
#define FND_CPP_OO_H
//#include <memory>
#include <map>
class Event;
class Base {
	public:
		virtual ~Base() {}// why? virtual
		virtual void act(Event const&) = 0;
		virtual void print() const = 0;
		int id() const { return m_id;}
		virtual void update() {}
		Base(int _id) : m_id(_id) {}
		virtual void addBase(Base* b) {}
		virtual void removeBase(int id) {}
	private:
		int m_id;
};

class Drived : public Base { // why public
	public:
		void act(Event const&);
		void print() const;
		Drived(int id);
		~Drived();
	private:
};

class Grouped : public Base {
public:
  void act(Event const &);
  void print() const;
	void addBase(Base* b);
	void removeBase(int id);
	Grouped(int id);
	~Grouped();
private:
  std::map<int, Base *> m_info;
};
#endif

