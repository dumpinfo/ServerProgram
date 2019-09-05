/*
 * =====================================================================================
 *
 *       Filename:  StlKnowledge.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt(fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <cassert>
#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <vector>
#include <array>

static void vectorPart();
static void dequePart();
static void listPart();
static void mapPart();
static void setPart();
static void unorderedMapPart();
static void unorderedSetPart();
static void stlAlgorithm();
static void arrayPart();

int main(int /* argc  */, char** /* argv */) {
	// STL是一个框架，将数据结构和算法进一步抽象。
	// 容器、迭代器、算法
	// Container
	// 1序列式容器 array/vector/deque/list/forward_list 数组 或者 指针 list
	// 2关联类容器 set/map/multiset/multimap 二叉树 红黑树 lgn
	// hash_map/hash_set
	// 3无顺序容器 unordered_map/unordered_set/unordered_multimap/unordered_multiset
	// hash table
	//
	// stack
	// queue
	// priority_queue
	// string
	// bitset bool sizeof(bool) == 1
	//
	// regex rand
	// thread async future time
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	// stl 容器的基本知识（常识部分)
	// 容器内元素的条件
	// （1）必须可以复制(copy)或者搬移(move) （隐含的条件是在拷贝和搬移的过程中应该没有副作用）
	
	struct BadStruct {
		BadStruct() : m_id(g_id++) {}
		~BadStruct() { std::cout << "bye\n";}
		// operator =
		int m_id;
		static int g_id;
	};
	// bool char int double pointer
	// reference, function
	// (2) 元素必须可以被赋值操作来复制或者搬移 （因为容器和算法对复写的要求）
	// =
	// （3）元素可以被销毁
	// 针对不同的容器还有特殊的要求
	// 对于序列式容器，元素必须有默认的构造函数
	// 对于某些操作，元素需要定义 == std::find
	// 对于关联式容器，排序准则默认的是 < > std::less
	// 无顺序容器，必须要提供一个hash函数 ==
	// stl容器里面存的是元素的值而不是引用
	// 那么我要问的是，到底我们的容器里面应该存的东西是什么呢？
	// class Player, Monster
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	// STL对于错误是怎么处理
	// 我们要记住的是STL的设计原则是效率优先，安全为次
	// 异常？STL自己却不怎么采用。









	//containerAllInterface();
























	vectorPart();
	listPart();
	mapPart();
	unorderedMapPart();
	unorderedSetPart();

	// 小小注意
	// set 并不会比 map 更省空间
	// 没有意外的情况下，优先考虑vector (why?)
	// log(n)的查找 和 近似 log(1) 的查找
	// 迭代器失效

	// stl 算法部分 常识部分
	stlAlgorithm();
}





static void mapPart() {
	// c++ 11 and above
	// map 默认的是用的std::less
	using Group = std::map<int, int>;
	Group a;
	auto ok = a.insert(std::make_pair(1,1)).second; // 注意返回值
	a[2] = 2; // 使用 [] 是有要求的
	a.size();
	auto isEmpty = a.empty();
	for(int i = 0; i < 10; ++i) a.emplace(i, i); // 注意emplace本身是有返回值的

	// 通过迭代器
	for(auto iter = a.begin(), iterEnd = a.end(); iter != iterEnd; ++iter) {
		// 注意迭代器访问的输出的key是有顺序的
		std::cout << "key: " << (*iter).first << " value: " << iter->second << " ";
	}
	std::cout << std::endl;

	// 通过key索引
	for(int i = 0; i < a.size(); ++i) {
		std::cout << a.at(i) << " "; // 注意a[i]的区别
	}

	std::cout << std::endl;
}


static void unorderedMapPart() {
	// c++ 11 and above
	// why not name hash_map? 为了保证代码的兼容
	using Group = std::unordered_map<int, int>;
	Group a;
	auto ok = a.insert(std::make_pair(1,1)).second; // 注意返回值
	a[2] = 2; // 使用 [] 是有要求的
	a.size();
	auto isEmpty = a.empty();
	for(int i = 0; i < 10; ++i) a.emplace(i, i); // 注意emplace本身是有返回值的

	// 通过迭代器
	for(auto iter = a.begin(), iterEnd = a.end(); iter != iterEnd; ++iter) {
		// 注意迭代器访问的输出是无序的
		std::cout << "key: " << (*iter).first << " value: " << iter->second << " ";
	}
	std::cout << std::endl;

	// 通过key索引
	for(int i = 0; i < a.size(); ++i) {
		std::cout << a.at(i) << " "; // 注意a[i]的区别
	}

	a.rehash(10); // ? 干了什么事情呢？
	std::cout << std::endl;
}


static void unorderedSetPart() {
	// c++ 11 and above
	using Group = std::unordered_set<int>;
	Group a;
	auto ok = a.insert(1).second; // 注意返回值
	a.size();
	auto isEmpty = a.empty();
	for(int i = 0; i < 10; ++i) a.emplace(i); // 注意emplace本身是有返回值的

	// 通过迭代器
	for(auto iter = a.begin(), iterEnd = a.end(); iter != iterEnd; ++iter) {
		// 注意迭代器访问的输出的是有顺序的
		std::cout << " value: " << *iter << " ";
	}
	std::cout << std::endl;
}

static void printInfoVersionOne();
static void sortPart();

static void stlAlgorithm() {
	// sort stable_sort
	// remove
	// find find_if
	// count count_if
	// copy copy_if (c++11)
	// swap (非常非常重要的一个函数，意想不到的重要)
	// random_shuffle shuffle
	// .......等等，请自行google
	// stl本身给我们提供了非常非常多的算法，可以替我们解决很多基本的问题，
	// 我们没有必要重新造轮子
	//
	// 一个矫情的例子
	printInfoVersionOne();

	sortPart();
}

static void printInfoVersionOne() {
  using DataStruct = std::vector<std::map<int, std::vector<int>>>;
  DataStruct complicateData;
  // fill data
  // 遍历所有的数据
  for (auto iterOne = complicateData.begin(); iterOne != complicateData.end();
       ++iterOne) {
    // do lot of things
    // ba ba ba
    // ba ba ba
    for (auto iterTwo = (*iterOne).begin(); iterTwo != (*iterOne).end();
         ++iterTwo) {
      // do lot of things
      // ba ba ba
      // ba ba ba
      for (auto iterThree = (*iterTwo).second.begin();
           iterThree != (*iterTwo).second.end(); ++iterThree) {

        // do lot of things
        // ba ba ba
        // ba ba ba
        // final we get the data
      }
    }
  }
}

static void sortPart() {
  std::vector<int> objects(1000);
  std::generate(std::begin(objects), std::end(objects),
                []() { return rand(); });
  std::sort(std::begin(objects), std::end(objects));
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	auto engine = std::default_random_engine(seed);
  std::shuffle(std::begin(objects), std::end(objects),
               engine);
	auto objects2{objects};
	std::stable_sort(std::begin(objects), std::end(objects));
  std::shuffle(std::begin(objects), std::end(objects),
               engine);
}


























template <typename T>
void containerAllInterface(T& a, T& b) {
	T c;
	T d(a); // copy
	T e = a; // copy
	T f(std::move(a)); // move
	auto iterB = b.begin();
	auto iterE = b.end();
	T g(iterB, iterE); // copy
	b.size(); // std::forward_list
	b.empty(); // return b.size() == 0;
	b.max_size();
	if(b == c) { // ==

	}
	if(b != d) { // !(b == d)

	}
	if(b < e) { // unordered_set unordered_map
		// b <= e
		// b > e
		// b >= e

	}
	e = b;
	e = std::move(b);
	e.swap(g); // std::array 线性的， O1
	swap(e,g); // 01 除了 std::array

	e.cbegin(); // -> const_iterator
	auto ea = e.cbegin();
	auto eea = e.begin();
	*eea; // -> ???? const &, &
	*ea; // -> const &

	e.cend();
	e.clear(); // not forward_list, but std::array
}

void test() {
	std::vector<int> a;
	std::vector<int> b;
	// ?? array forward_list unordered_map unordered_set
	containerAllInterface(a,b);
}













template<typename C>
void checkSize(C& c) {
	if(c.size() > 3) {
		c[3] = 10;
	}
	//c.at(3) = 10;
}











void arrayPart() {
	// array 实际上是对c/c++语言中原生数组进行的封装
	// namespace std {
	// template<typename T, size_t N>
	// class array;
	// }
	// 特点：内存分配在栈（stack），绝对不会重新分配，随机访问元素
	int abc[100];
	std::array<int, 100> a;
	std::array<int, 100> b = {};
	// 以上两者的区别
	
	std::array<int, 5> obj = {1,2,3,4,5};
	std::array<int, 5> obj2 = {1,0};
	// 接口
	a.empty(); // nerver be true if size > 0
	a.size();
	a.max_size();
	// operator == < != > <= >=
	auto aa = a;

	aa.swap(a);
	swap(aa, a);
	// 访问元素
	a[1];
	a.at(1);
	a.front();
	a.back();
	checkSize(a);

	// 迭代器相关
	a.begin();
	a.end();
	a.cbegin();
	a.cend();
	a.rbegin();
	a.rend();
	a.crbegin();
	a.crend();

	// 和C的接口互用
	std::array<char, 100> carr;
	strcpy(&carr[0], "hello world\n"); // more better use carr.data();
	printf("%s", &carr[0]); // more better use carr.data()
	// 错误的用法
	printf("%s", carr.begin());

	// 特殊的地方
	auto info = std::get<1>(carr);
	carr.fill(0);

	// 异常exception
	// c.at(pos);
	// copy move swap
}











static void vectorPart() {
	// vector 是c++98中引入的动态数组（dynamic array）
	// namespace std {
	// template<typename T, typename Allocator = allocator<T>>
	// class vector;
	// }
	// 特点随机访问元素，末端添加删除元素效率高。前端和中间删除和添加元素效率低，
	// 存在当前容器大小和容量的关系
	using Group = std::vector<float>;
	//typedef std::vector<float> Group;

	Group a;
	Group b = a;
	Group c(a);
	Group d(10);
	Group e(10, 1.0f);
	Group f(e.begin(), e.end());
	Group g({1.0f, 2.0f, 3.0f});
	Group h = {1.0f, 3.0f, 4.0f}; // initialize list
	
	d.empty();
	d.size();
	d.max_size();
	d.capacity();
	d.reserve(100);
	d.shrink_to_fit(); // c++11
	// operator == != < > <= >=
	
	// 赋值
	b = g;
	b.assign(3, 1.0f); // { 1.0f, 1.0f, 1.0f}
	b.assign(g.begin(), g.end()); // b = g
	b.assign({1.0f, 2.0f, 3.0f}); //
	
	// 交换
	b.swap(a); // vector
	std::swap(a,b);

	// 元素访问
	b[0];
	b.at(0); // std::out_of_range
	if(b.empty()) {
		b.front(); // undefined
		b.back(); // undefined
	}
	b.front();
	b.back();

	// 迭代器相关
	a.begin();
	a.end();
	a.cbegin();
	a.cend();
	a.rbegin();
	a.rend();
	a.crbegin();
	a.crend();

	a.pop_back(); // maybe wrong, undefined
	// single thread
	// multithread maybe wrong
	if(!a.empty()) a.pop_back();

	//
	b.erase(b.begin());
	b.erase(b.begin(), b.end());

	b.push_back(10.0f);
	b.pop_back();
	auto iter = b.insert(b.end(), 100.0f);
	iter = b.insert(b.end(), 10, -10.0f);
	b.insert(b.end(), h.begin(), h.end());
	b.emplace(b.end(), 10.0f); // c++11
	b.emplace_back(10.0f); // c++11 && move copy&&
	// b.size() == 100
	b.resize(10);
	// b.size() == 10
	b.resize(100, 1.0f);
	b.resize(100000);
	b.clear(); // notice
	b.shink_to_fit(); // c++11


	// 和C的接口互用
	std::vector<char> carr(100, 0);
	strcpy(&carr[0], "hello world\n"); // more better use carr.data();
	printf("%s", &carr[0]); // more better use carr.data()
	// 错误的用法
	printf("%s", carr.begin());

	// 异常
	// （1） push_back
	// (2) 元素 move/copy 没有异常的话， insert emplace emplace_back push_back
	// (3) pop_back
	// (4) 元素 move/copy 没有异常的话，erase
	// (5) swap clear
	
	// 特殊
	// std::vector<bool> never use it


}
















static void dequePart() {
	// deque 是c++98中引入的动态数组（dynamic array）
	// namespace std {
	// template<typename T, typename Allocator = allocator<T>>
	// class deque;
	// }
	// 特点随机访问元素，末端和头部添加删除元素效率高。中间删除和添加元素效率低，
	// 元素的访问和迭代比vector要慢，迭代器不能是普通的指针
	using Group = std::deque<float>;

	Group a;
	Group b = a;
	Group c(a);
	Group d(10);
	Group e(10, 1.0f);
	Group f(e.begin(), e.end());
	Group g({1.0f, 2.0f, 3.0f});
	Group h = {1.0f, 3.0f, 4.0f};
	
	d.empty();
	d.size();
	d.max_size();
	// 和vector不同，deque不提供以下的函数
	//d.capacity();
	//d.reserve(100);
	d.shrink_to_fit();
	// operator == != < > <= >=
	
	// 赋值
	b = g;
	b.assign(3, 1.0f);
	b.assign(g.begin(), g.end());
	b.assign({1.0f, 2.0f, 3.0f});
	
	// 交换
	b.swap(a);
	std::swap(a,b);

	// 元素访问
	b[0];
	b.at(0);
	b.front();
	b.back();

	// 迭代器相关
	a.begin();
	a.end();
	a.cbegin();
	a.cend();
	a.rbegin();
	a.rend();
	a.crbegin();
	a.crend();

	a.pop_back(); // maybe wrong
	if(!a.empty()) a.pop_back();

	b.erase(b.begin());
	b.erase(b.begin(), b.end());

	b.push_back(10.0f);
	b.pop_back();
	b.push_front(1.2f);
	b.emplace_front(1.3f);
	auto iter = b.insert(b.end(), 100.0f);
	iter = b.insert(b.end(), 10, -10.0f);
	b.insert(b.end(), h.begin(), h.end());
	b.emplace(b.end(), 10.0f);
	b.emplace_back(10.0f);
	b.resize(10);
	b.resize(100, 1.0f);
	b.clear(); // notice
	b.shink_to_fit();



	// 异常
	// （1） push_back push_front
	// (2) 元素 move/copy 没有异常的话， insert emplace emplace_back push_back
	// (3) pop_back
	// (4) 元素 move/copy 没有异常的话，erase
	// (5) swap clear

}







static void listPart() {

	// list 是c++98中引入的双向串列（doubley linked list）
	// namespace std {
	// template<typename T, typename Allocator = allocator<T>>
	// class list;
	// }
	// 特点不支持随机访问元素，访问头部和尾部元素速度快
	// 任何位置插入删除元素都很快，常量时间内完成
	// 插入和删除不会造成迭代器失效
	// 对于异常支持的好，出现异常对于list而言，要不成功，要不什么影响没有
	using Group = std::list<float>;

	Group a;
	Group b = a;
	Group c(a);
	Group d(10);
	Group e(10, 1.0f);
	Group f(e.begin(), e.end());
	Group g({1.0f, 2.0f, 3.0f});
	Group h = {1.0f, 3.0f, 4.0f};
	
	d.empty();
	d.size();
	d.max_size();
	// 和vector不同，list不提供以下的函数
	//d.capacity();
	//d.reserve(100);
	//d.shrink_to_fit();
	// operator == != < > <= >=
	
	// 赋值
	b = g;
	b.assign(3, 1.0f);
	b.assign(g.begin(), g.end());
	b.assign({1.0f, 2.0f, 3.0f});
	
	// 交换
	b.swap(a);
	std::swap(a,b);

	// 元素访问,不能随机访问
	//b[0];
	//b.at(0);
	b.front();
	b.back();

	// 迭代器相关
	a.begin();
	a.end();
	a.cbegin();
	a.cend();
	a.rbegin();
	a.rend();
	a.crbegin();
	a.crend();
	auto iterBegin = a.begin();
	//assert(a.size() >= 10);
	//for(int i = 0;i < 5; ++i) ++iterBegin;
	//std::advance(iterBegin, 4);
	//auto iter5 = std::next(iterBegin, 4);


	a.pop_back(); // maybe wrong
	if(!a.empty()) a.pop_back();

	b.erase(b.begin());
	b.erase(b.begin(), b.end());

	b.push_back(10.0f);
	b.pop_back();
	b.push_front(1.2f);
	b.emplace_front(1.3f);
	auto iter = b.insert(b.end(), 100.0f);
	iter = b.insert(b.end(), 10, -10.0f);
	b.insert(b.end(), h.begin(), h.end());
	b.emplace(b.end(), 10.0f);
	b.emplace_back(10.0f);
	b.resize(10);
	b.resize(100, 1.0f);
	// 算法
	b.remove(1.0f);
	b.remove_if([](auto v) { return v > 100.0f;});
	b.reverse(); // 1 2 3 4 -> 4 3 2 1
	//std::sort(a.begin(), a.end());
	b.sort(); // <
	g.sort(); //
	b.merge(g);
	c.unique(); // 1 1 2 2 1 1 3 4 -> 1 2 1 3 4
	c.splice(c.begin(), b);
}







static void forwardListPart() {

	// forward_list 是c++11中引入的单向串列（singly linked list）
	// namespace std {
	// template<typename T, typename Allocator = allocator<T>>
	// class forward_list;
	// }
	// 特点不支持随机访问元素，访问头部元素速度快
	// "forward_list 和自己手写的c-style singly linked list相比，
	// 没有任何时间和空间上的额外开销。任何性质如果和这个目标抵触，我们放弃该特征。"
	// 任何位置插入删除元素都很快，常量时间内完成
	// 插入和删除不会造成迭代器失效
	// 对于异常支持的好，出现异常对于forward_list而言，要不成功，要不什么影响没有
	using Group = std::forward_list<float>;

	Group a;
	Group b = a;
	Group c(a);
	Group d(10);
	Group e(10, 1.0f);
	Group f(e.begin(), e.end());
	Group g({1.0f, 2.0f, 3.0f});
	Group h = {1.0f, 3.0f, 4.0f};
	
	d.empty();
	//d.size();
	d.max_size();
	// 和vector不同，forward_list不提供以下的函数
	//d.capacity();
	//d.reserve(100);
	//d.shrink_to_fit();
	// operator == != < > <= >=
	
	// 赋值
	b = g;
	b.assign(3, 1.0f);
	b.assign(g.begin(), g.end());
	b.assign({1.0f, 2.0f, 3.0f});
	
	// 交换
	b.swap(a);
	std::swap(a,b);

	// 元素访问,不能随机访问
	//b[0];
	//b.at(0);
	b.front();
	//b.back();

	// 迭代器相关
	a.begin();
	a.end();
	a.cbegin();
	a.cend();
	//auto iter = a.before_begin();
	//*iter; // undefined
	a.before_begin();
	c.cbefore_begin();
//	a.rbegin();
//	a.rend();
//	a.crbegin();
//	a.crend();
	auto iterBegin = a.begin();


	//a.pop_back(); // maybe wrong
	//if(!a.empty()) a.pop_back();

	// auto iter = b.erase(b.begin());
	b.erase_after(b.before_begin()); // return void
	b.erase_after(b.before_begin(), b.end()); // return void

	//b.push_back(10.0f);
	//b.pop_back();
	b.push_front(1.2f);
	b.emplace_front(1.3f);
	auto iter = b.insert_after(b.before_begin(), 100.0f);
	iter = b.insert_after(b.before_begin(), 10, -10.0f);
	b.insert_after(b.before_begin(), h.begin(), h.end());
	//b.emplace(b.end(), 10.0f);
	//b.emplace_back(10.0f);
	b.resize(10);
	b.resize(100, 1.0f);
	// 算法
	b.remove(1.0f);
	b.remove_if([](auto v) { return v > 100.0f;});
	b.reverse(); // 1 2 3 4 -> 4 3 2 1
	//std::sort(a.begin(), a.end());
	b.sort(); // <
	g.sort(); //
	b.merge(g);
	c.unique(); // 1 1 2 2 1 1 3 4 -> 1 2 1 3 4
	c.splice_after(c.before_begin(), b);

	Group forlist = { 1, 2, 3, 4, 5};
	auto fiter = forlist.before_begin();
	for(int i = 0; i < 2; ++i) ++fiter;
	forlist.insert_after(fiter, 10);

}





static void setPart() {

	// set multiset 是c++98中引入的二叉树数据结构
	// namespace std {
  // template<typename T, typename Compare = less<T>, typename Allocator =
  // allocator<T>>
  // class set;
	//
  // template<typename T, typename Compare = less<T>, typename Allocator =
  // allocator<T>>
  // class multiset;
  // }
  // 特点自动将元素排序
  // 插入和删除查找O(logn), 1000, 20
	// 必须元素必须支持严格的弱顺序
	// （1） x < y == true, y < x == false
	// (2) x < y == true, y < z == true, x < z == true
	// (3) x < x === false
	// (4) a == b, b == c, c == a
	// 不能改变元素的值
	//
	// 辅助的类
	// namespace std {
	// template<typename T1, typename T2>
	// struct pair {
	// T1 first;
	// T2 second;
	// };
	// }
	using Group = std::set<float>;
	Group a;
	Group b = a;
	Group c(a);
	Group d(c.begin(), c.end());
	Group g({1.0f, 4.0f, 3.0f});
	// 1.0f
	// 1.0f 4.0f
	// 1.0f 3.0f 4.0f -> 1.0f 4.0f 3.0f
	Group h = {1.0f, 3.0f, 4.0f};
	
	d.empty();
	d.size();
	d.max_size();
	// operator == != < > <= >=
	// special
	auto keycomp = c.key_comp();
	auto valuecomp = c.value_comp();
	
	// 赋值
	b = g;
	
	// 交换
	b.swap(a);
	std::swap(a,b);


	// 迭代器相关
	a.begin();
	a.end();
	a.cbegin();
	a.cend();
	a.rbegin();
	a.rend();
	a.crbegin();
	a.crend();
	auto iterBegin = a.begin();

	//算法函数
	// set count 0 1
	// multiset count >= 0
	auto num = a.count(1.0f);
	auto findIter = a.find(1.0f);
	if(findIter == a.end()) {
		// not finded
	} else {
		*findIter;
	}
	auto lower = a.lower_bound(1.0f);
	if(lower != a.end()) {
		if(*lower == 1.0f) {
			// has 1.0f
		}
	}
	auto high = a.upper_bound(1.0f);
	auto range = a.equal_range(1.0f); // return std::make_pair(a.lower_bound(1.0f), a.upper_bound(1.0f));

	auto eraseIter = b.erase(b.begin());
	eraseIter = b.erase(b.begin(), b.end());

	auto state = b.insert(100.0f); // state is a pair<Iterator, bool>
	auto insertIter = b.insert(c.begin(), c.end());
	b.emplace(10.0f);
	b.emplace_hint(b.end(), 100.0f);
}




static void mapPart() {

	// map multimap是c++98中引入的二叉树数据结构
	// namespace std {
  // template<typename Key, typename T, typename Compare = less<Key>, typename Allocator =
  // allocator<pair<const Key, T>>
  // class map;
  // template<typename Key, typename T, typename Compare = less<Key>, typename Allocator =
  // allocator<pair<const Key, T>>
  // class multimap;
	// }
  // 特点自动将元素排序
  // 插入和删除查找O(logn)
	// 必须Key元素必须支持严格的弱顺序
	// （1） x < y == true, y < x == false
	// (2) x < y == true, y < z == true, x < z == true
	// (3) x < x === false
	// (4) a == b, b == c, c == a
	// 不能改变Key元素的值
	//
	using Group = std::map<int,std::string>;
	Group a;
	Group b = a;
	Group c(a);
	Group d(c.begin(), c.end());
	Group g({{1, "a"}, {2,"test"}, {3, "test"}});
	
	d.empty();
	d.size();
	d.max_size();
	// operator == != < > <= >=
	// special
	auto keycomp = c.key_comp();
	auto valuecomp = c.value_comp();
	
	// 赋值
	b = g;
	
	// 交换
	b.swap(a);
	std::swap(a,b);


	// 迭代器相关
	a.begin();
	a.end();
	a.cbegin();
	a.cend();
	a.rbegin();
	a.rend();
	a.crbegin();
	a.crend();
	auto iterBegin = a.begin();

	//算法函数
	// map count 0 1
	// multimap count >= 0
	auto num = a.count(1);
	auto findIter = a.find(1);
	if(findIter == a.end()) {
		// not finded
	} else {
		const std::pair<int, std::string>& obj = *findIter;
		//*findIter; // std::pair<const int, std::string>&
	}
	auto lower = a.lower_bound(1);
	if(lower != a.end()) {
		if(*lower.first == 1) {
			// has 1
		}
	}
	auto high = a.upper_bound(1);
	auto range = a.equal_range(1); // return std::make_pair(a.lower_bound(1), a.upper_bound(1));

	auto eraseIter = b.erase(b.begin());
	eraseIter = b.erase(b.begin(), b.end());

	auto state = b.insert(std::make_pair(100, "good")); // state is a pair<Iterator, bool>
	auto insertIter = b.insert(c.begin(), c.end());
	b.emplace(std::make_pair(10, "has it"));
	b.emplace(11, std::string("again")); // b.emplace( std::pair<const int,std::string>(10, std::string("again"));
	b.emplace(12, "third"); // b.emplace(std::pair<const int, std::string>(10, "third"));
	b.emplace_hint(b.end(), 13, "haha");

	// []
	// auto string
	auto& info = b[10];
	// [] -> auto iter = b.insert(std::make_pair(13, std::string())).first; return (*iter).second;
	b[13];

	// at
	try {
		auto& findInfo = b.at(10); // const
	} catch(...) {

	}
	auto findIter = b.find(10);
	if(findIter != std::end(b) /* b.end() */) {
		auto& v = (*findIter).second;
	} else {

	}

	auto info = get_default(b, 10);
	if(info.empty()) {

	} else {

	}
}

template <class Map>
typename Map::mapped_type get_default(
    const Map &map, const typename Map::key_type &key,
    const typename Map::mapped_type &dflt = typename Map::mapped_type()) {
  auto pos = map.find(key);
  return (pos != map.end() ? pos->second : dflt);
}







static void unorderedSetAndMapPart() {

	// unordered_multiset unordered_set
	// unordered_map unordered_multimap是c++11中以hash table为基础的，内部元素没有明确的顺序的容器
	// namespace std {
  // template<typename Key, typename T, typename Hash = hash<Key>, typename
  // EqPred = equal_to<Key>,  typename Allocator =
  // allocator<pair<const Key, T>>
  // class unorderd_map;
  // template<typename Key, typename T, typename Hash = hash<Key>, typename
  // EqPred = equal_to<T>,typename Allocator =
  // allocator<pair<const Key, T>>
  // class multimap;
  // template<typename T, typename Hash = hash<T>, typename
  // EqPred = equal_to<T>,  typename Allocator =
  // allocator<T>>
  // class unorderd_set;
  // template<typename T, typename Hash = hash<T>, typename
  // EqPred = equal_to<T>,  typename Allocator =
  // allocator<T>>
  // class unorderd_multiset;
  // }
  // 插入和删除查找O(1)
  // 不能改变Key元素的值
  //
        using Group = std::unordered_map<int,std::string>;
	Group a;
	Group b = a;
	Group c(a);
	Group d(c.begin(), c.end());
	Group g({{1, "a"}, {2,"test"}, {3, "test"}});
	
	d.empty();
	d.size();
	d.max_size();
	// operator == !=
	//  special
	// 赋值
	b = g;
	// 交换
	b.swap(a);
	std::swap(a,b);


	// 迭代器相关
	a.begin();
	a.end();
	a.cbegin();
	a.cend();
	a.rbegin();
	a.rend();
	a.crbegin();
	a.crend();
	auto iterBegin = a.begin();

	//算法函数
	// map count 0 1
	// multimap count >= 0
	auto num = a.count(1);
	auto findIter = a.find(1);
	if(findIter == a.end()) {
		// not finded
	} else {
		const std::pair<int, std::string>& obj = *findIter;
		//*findIter; // std::pair<const int, std::string>&
	}
	auto lower = a.lower_bound(1);
	if(lower != a.end()) {
		if(*lower.first == 1) {
			// has 1
		}
	}
	auto high = a.upper_bound(1);
	auto range = a.equal_range(1); // return std::make_pair(a.lower_bound(1), a.upper_bound(1));

	auto eraseIter = b.erase(b.begin());
	eraseIter = b.erase(b.begin(), b.end());

	auto state = b.insert(std::make_pair(100, "good")); // state is a pair<Iterator, bool>
	auto insertIter = b.insert(c.begin(), c.end());
	b.emplace(std::make_pair(10, "has it"));
	b.emplace(11, std::string("again")); // b.emplace( std::pair<const int,std::string>(10, std::string("again"));
	b.emplace(12, "third"); // b.emplace(std::pair<const int, std::string>(10, "third"));
	b.emplace_hint(b.end(), 13, "haha");

	// []
	// auto string
	auto& info = b[10];
	// [] -> auto iter = b.insert(std::make_pair(13, std::string())).first; return (*iter).second;
	b[13];

	// at
	try {
		auto& findInfo = b.at(10); // const
	} catch(...) {

	}
	auto findIter = b.find(10);
	if(findIter != std::end(b) /* b.end() */) {
		auto& v = (*findIter).second;
	} else {

	}

	auto info = get_default(b, 10);
	if(info.empty()) {

	} else {

	}
}

