/*
 * =====================================================================================
 *
 *       Filename:  threadKnowledge.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Saturday, March 05, 2016 01:19:06 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt(fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <cassert> // why c?
#include <cstdlib> // rand srand
#include <ctime> // time clock
#include <algorithm>
#include <future> // async
#include <iostream> // cout endl
#include <numeric> // accumulate
#include <thread> // thread
#include <vector> // vector

using Group = std::vector<int64_t>;
static void versionOne(const Group&);
static void versionTwo(const Group&);
static void versionThree(const Group&);
static Group buildBigData();

int main(int /* argc  */, char** /* argv */) {
	std::srand(time(NULL));
	auto bigData = buildBigData();
	// c++11关于线程方面的一些基本用法
	versionOne(bigData);
	versionTwo(bigData);
	versionThree(bigData);




	// 没有提到的还有很多很多东西
	// 线程间如何同步？？
	// 抛出异常会怎样？？
	// condition_variable 是什么东西？怎么用？
	// mutex 死锁怎么办？
	// atomic 原子操作,你会正确的使用么？
	return EXIT_SUCCESS;
}

static int randomInt() { return rand() % 10000;}

static Group buildBigData() {
	Group v(100000000); // 10000W
	std::generate(v.begin(), v.end(), randomInt);
	return v;
}

void versionOne(const Group &bigData) {
  auto clockStart = clock();
  auto total =
      std::accumulate(bigData.begin(), bigData.end(), Group::value_type(0));
  auto clockEnd = clock();
  std::cout << "versionOne ave is " << total / bigData.size() << " use time is "
            << (clockEnd - clockStart) << std::endl;
}

static void caculateTotal(Group::const_iterator b, Group::const_iterator e,
                          Group::value_type *result) {
  assert(result);
  *result = std::accumulate(b, e, Group::value_type(0));
}

void versionTwo(const Group& bigData) {
  auto clockStart = clock();
  auto middle = bigData.begin() + (bigData.size() / 2);
  Group::value_type frontPart = 0;
  std::thread threadA(caculateTotal, bigData.begin(), middle, &frontPart);
  ++middle;
  Group::value_type backPart =
      std::accumulate(middle, bigData.end(), Group::value_type(0));
  threadA.join(); // ?? why join?
  auto clockEnd = clock();
  std::cout << "versionTwo ave is " << (backPart + frontPart) / bigData.size()
            << " use time is " << (clockEnd - clockStart)
						<< std::endl;
}

static void versionThree(const Group& bigData) {

  auto clockStart = clock();
  auto middle = bigData.begin() + (bigData.size() / 2);
  Group::value_type frontPart = 0;
	// async(std::launch::async
	// async(std::launch::deferred
  auto s = std::async(caculateTotal, bigData.begin(), middle, &frontPart);
  ++middle;
  Group::value_type backPart =
      std::accumulate(middle, bigData.end(), Group::value_type(0));
  s.get();

  auto clockEnd = clock();
  std::cout << "versionTwo ave is " << (backPart + frontPart) / bigData.size()
            << " use time is " << (clockEnd - clockStart) << std::endl;
}

