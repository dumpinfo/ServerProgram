/*
 * =====================================================================================
 *
 *       Filename:  LearnThread.cpp
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
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <atomic>
#include <mutex>
//enum memory_order {
//
//  memory_order_relaxed,
//  memory_order_consume,
//  memory_order_acquire,
//  memory_order_release,
//  memory_order_acq_rel,
//  memory_order_seq_cst
//};

// 为什么用多线程来做服务器？
// （1）当前的机器的单核红利已经结束了
// process(linux fork windows CreateProcess, signal) thread (POSIX threads)
// （2）多线程拥有自身的优势
// （3）API日益成熟，操作系统和标准库都已经支持了多线程
// 要在数据IO和计算找到平衡点
// 多线程的编程，mutilthread goto
// 可能的问题包括：
// （1）死锁；
// （2）乱序
// （3）并发访问数据造成的问题；
// （4）低效率

// c++11给我们带来的新概念
// （1）高阶接口；(async, future)
// （2）低阶接口；(thread, mutex)
//
//
//沉重的计算方法
double caculate(double v) {
  if (v <= 0)
    return v;
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // 实际上计算机算这个东西是很快的，但是我们假装它算的很慢 :）
  return sqrt((v * v + std::sqrt((v - 5) * (v + 2.5)) / 2.0) / v);
}
// for_each
template <typename Iter, typename Fun>
double visitRange(std::thread::id id, Iter iterBegin, Iter iterEnd, Fun func) {
	auto curId = std::this_thread::get_id();
	if(id == curId)
		std::cout << curId << " hello main thread\n";
	else std::cout << curId << " hello work thread\n";
  double v = 0;
  for (auto iter = iterBegin; iter != iterEnd; ++iter) {
    v += func(*iter);
  }
  return v;
}

class Counter {
public:
	void addCountAndResouce(int r) {
		std::lock_guard<std::mutex> lock(m_mutex);
		addCount();
		addResource(r);
	}
	int count() const {
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_count;
	}
	int aveResource() {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_count == 0) {
			return 1;
		}
		return m_totalResource / m_count;
	}
  Counter() : m_count{0},m_totalResource{0} {}

private:
	int m_count;
	int m_totalResource;
	mutable std::mutex m_mutex;
	void addResource(int r) {m_totalResource++;}
  void addCount() { m_count++; } // 写入寄存器 寄存器加1 写入内存
	// ++ -- + - * /
	// expert fetch_add fetch_sub
	//int m_count;
};

int work(int a) {
  // do some thing
  return a + a;
}

void debugPrintInfo(Counter& c) {
	std::cout << c.aveResource() << std::endl;
}


template <class Iter>
void realWork(Counter &c, double &totalValue, Iter b, Iter e) {
  for (; b != e; ++b) {
		try {
    totalValue += work(*b);
		// print some vaule
	//	debugPrintInfo(c);
    c.addCountAndResouce(1);
		} catch(...) {
		}
  }
}
void printAll(int a, int b, int c) {
	std::cout << a << " " << b << " " << c << std::endl;
}

void add(int a, int b, int& c) {
	c = a + b;
}

void printString(const std::string& info, const std::string& info2) {
	std::cout << "hello " << info << " " << info2 << "\n";
}

void testThreadInit() {
	int a = 3;
	int b = 4;
	int c = 5;
	std::thread t([=]{printAll(a,b,c);});
	t.join();
	std::thread t2(printAll, a, b, c);
	t2.join();

	std::thread t3([=, &c]{add(a,b,c);});
	t3.join();
	std::cout << "after add " << c << std::endl;
	std::thread t4(add, a, b, std::ref(c));
	t4.join();

	std::string abc("abc");
	std::string def("def");

	std::thread t5([&]{printString(abc,def);});
	t5.join();
	std::thread t6(printString, abc, def);
	t6.join();
	std::thread t7(printString, std::cref(abc), std::cref(def));
	t7.join();


}

bool printStep(Counter &c, int maxCount) {
  auto count = c.count();
  if (count == maxCount) {
    std::cout << " ok finished \n";
		return true;
	}
	return false;
}


struct BankAccount {
	BankAccount(int b) : Balance(b) {}
	int Balance;
	std::mutex Mutex;
};

template<typename T>
class Lock {
	public:
		Lock(T& m) : m_mutex(m) { m.lock();}
		~Lock() { m_mutex.unlock();}
	private:
		T& m_mutex;
};

void transferMoney(BankAccount &a, BankAccount &b, int money) {
	std::lock(a.Mutex, b.Mutex /* ..... */);
	std::lock_guard<std::mutex> lockA(a.Mutex, std::adopt_lock);
	std::lock_guard<std::mutex> lockB(b.Mutex, std::adopt_lock);

	if (a.Balance <= money)
		return;
	a.Balance -= money;
	b.Balance += money;
//  if (&a == &b)
//    return;
//  if (&(a.Mutex) < &(b.Mutex)) {
//    std::lock_guard<std::mutex> lockA(a.Mutex);
//    std::lock_guard<std::mutex> lockB(b.Mutex);
//
//    if (a.Balance <= money)
//      return;
//    a.Balance -= money;
//    b.Balance += money;
//  } else {
//    std::lock_guard<std::mutex> lockA(b.Mutex);
//    std::lock_guard<std::mutex> lockB(a.Mutex);
//    if (a.Balance <= money)
//      return;
//    a.Balance -= money;
//    b.Balance += money;
//  }
}

// BankAccount alice(100);
// BankAccount bob(100);
// threa1
// transferMoney(alice, bob, 10); // when call lockB
// thread2
// transferMoney(bob, alice, 10); // when call lockB



int main() {
	//testThreadInit();
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";
	std::vector<int> vec;
	double totalValue = 0;
	for(int i = 0; i < 10000000; ++i) {
		vec.push_back(rand() % 100);
	}
	Counter counter;
	realWork(counter, totalValue, vec.begin(), vec.end());
	// do work
	std::cout << "total times: " << counter.count() << " " << totalValue<< std::endl;

	totalValue = 0;
	Counter counter2;
	std::thread printCount([&counter2] {
			while (!printStep(counter2, 10000000))
			;
			});
	auto iter = vec.begin() + (vec.size() / 3);
	auto iter2 = vec.begin() + (vec.size() / 3 * 2);
	std::thread b([&counter2, &totalValue, iter, iter2] {
			realWork(counter2, totalValue, iter, iter2);
			});
	auto end = vec.end();
	double totalC = 0;
	std::thread c([&counter2, &totalC, iter2, end] {
			realWork(counter2, totalC, iter2, end);
			});

	double totalM = 0;
	realWork(counter2, totalM, vec.begin(), iter);
	b.join();
	c.join();
	auto realTotalCount = counter2.count();
	totalValue += totalC + totalM;
	std::cout << "total times use multithread: " << realTotalCount << " " << totalValue << std::endl;
	printCount.join();
	// (1) 如果没有必要的话，线程间不要共享资源
}

