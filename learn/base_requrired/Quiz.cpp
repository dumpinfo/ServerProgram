/*
 * =====================================================================================
 *
 *       Filename:  Quiz.cpp
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
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
void transOrder(char*);
void transOrderC(char*);

// 难度3~8
// 假设有一个容器里面存的数据是无序，
// 例如是 1 5 3 5 6 7 100
// 函数传入这个容器 和 一个位置值 比如是 3
// 函数将这个容器的内容根据传入的位置进行调整，经过调整后
// 变成6 7 100 5 1 5 3
// 什么意思呢，就是在位置3之后的放到前头，位置3之前的放到后面
// changeOrder({1,2,3}, 0) -> 2 3 1
// changeOrder({1,2,3}, 1) -> 3 2 1
// changeOrder({1,2,3}, 2) -> 3 1 2
// 假设我们不考虑pos无效的情况 pos >= 0 && pos < objects.size()
void changeOrder(std::vector<int>& objects, int pos) {
  assert(pos >= 0);
  assert(pos < objects.size());
  std::rotate(objects.begin(), objects.begin() + pos, objects.end());
  std::rotate(objects.begin(), objects.begin() + 1,
              objects.begin() + (objects.size() - pos));
}

std::vector<int> changeOrderCopy(const std::vector<int>& objects, int pos) {
	assert(pos >= 0);
	assert(pos < objects.size());
	std::vector<int> v(objects.begin() + pos + 1, objects.end());
	v.push_back(objects[pos]);
	v.insert(v.end(), objects.begin(), objects.begin() + pos);
	return v;
}














struct Node {
	Node* next;
	int value;
};

static void printNodeList(Node *n) {
  while (n) {
    std::cout << n->value << " ";
    n = n->next;
  }
  std::cout << "\n";
}

static void quizOne();
static void quizTwo();
static void quizThree();
static void quizFour();

void quickSort(int* arr, size_t size);

int main(int argc, char** argv) {
	char abc[] = "abc";
	char def[] = "goodman";
	transOrderC(abc);
	transOrder(def);
	std::cout << "abc " << abc << "\n";
	std::cout << "def " << def << "\n";
	//quizOne();
	std::vector<int> info = {1,23,3,4,233,12, 33};
	quickSort(info.data(), info.size());
	for(auto v : info) {
		std::cout << v << " ";
	}
	std::cout << std::endl;
}

static Node* reverseList(Node* node) {
	// do what
	//
	//
	//return what??
	return 0;
}


static void quizOne() {
	// 如何翻转一个单项列表
	// 3 -> 2 -> 1
	// 翻转后变成 1 -> 2 -> 3
	Node* n = 0;
	for(int i = 1; i < 4; ++i) {
		Node* node = new Node();
		node->value = i;
		node->next = n;
		n = node;
	}
	printNodeList(n);
	n = reverseList(n);
	printNodeList(n);

	// I know has memery leak. no problem just a test
}




class A {
	public:
		virtual ~A(){}
		virtual A* clone() const { return new A();}
};

class B : public A {
	public:
		virtual B* clone() const { return new B();}
};































void changeOrder(char* data) {
 //apple
 /// ,.,.,
 //elppa
}









































static void printGroup(const std::string& header,  const std::vector<int>& g) {
	std::cout << header << " ";
	std::copy(g.begin(), g.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
}

void quizThree() {
	std::vector<int> group;
	group.push_back(1);
	group.push_back(2);
	group.push_back(3);
	std::vector<int> group2 = group;
	std::vector<int> group3 = group;
	printGroup("origin", group);
	changeOrder(group, 0);
	printGroup("first", group);
	changeOrder(group2, 1);
	printGroup("second", group2);
	changeOrder(group3, 2);
	printGroup("third", group3);
}

static bool hasCircle(Node* n) {
	if(!n) return false;
	Node* slow = n->next;
	if(!slow) return false;
	Node* fast = slow->next;
	while(slow && fast) {
		if(slow == fast) return true;
		slow = slow->next;
		fast = fast->next;
		if(!fast) return false;
		fast = fast->next;
	}
	return false;
}

static void quizTwo() {
  typedef std::vector<int> Group;
  Group playerIds;
  for (int i = 0; i < 100; ++i) playerIds.push_back(rand() % 100);
  Group::iterator first = std::find(playerIds.begin(), playerIds.end(), 0);
  Group::iterator last = std::find(playerIds.begin(), playerIds.end(), 99);
  *last = 100;
  std::copy(first, last, std::ostream_iterator<int>(std::cout, ","));
	std::cout << std::endl;
  playerIds.insert(--playerIds.end(), 101);
  std::copy(first, last, std::ostream_iterator<int>(std::cout, ","));
	std::cout << std::endl;
}

class BigObject {
	private:
		char m_manyData[100000];
};
static void quizFour() {
	std::map<int, BigObject> group;
	// 假设我们已经在group里面放了很多的数据
	int whatYouFind = 100;
	for(std::map<int,BigObject>::iterator iter = group.begin();
			iter != group.end(); ++iter) {
		//do some other thing .....
		if((*iter).first == whatYouFind) {
			BigObject obj;
			// do something .....
			group[whatYouFind] = obj;
		}
	}
}








void transOrderC(char* data) {
	auto l = strlen(data);
	if(l <= 1) return;
	auto m = l / 2;
	auto start = 0;
	while(start < m) {
		std::swap(data[start], data[l - start -1]);
		++start;
	}
}

void transOrder(char* data) {
	auto l = strlen(data);
	std::reverse(data, data + l);
}

size_t quickSortPartition(int* arr, size_t b, size_t e) {
	auto pos = b;
	while(b < e) {
		if(arr[b] < arr[e-1]) {
			std::swap(arr[b], arr[pos]);
			++pos;
		}
		++b;
	}
	std::swap(arr[e - 1], arr[pos]);
	return pos;

}

void quickSort(int* arr, size_t b, size_t e) {
  if (b < e) {
    auto p = quickSortPartition(arr, b, e);
    quickSort(arr, b, p);
    quickSort(arr, p + 1, e);
  }
}

void quickSort(int* arr, size_t size) {
	quickSort(arr, 0, size);
}






























int main() {
	int a = 0xFF;//00000000000000000000000011111111
	int b = a << 33;
	std::cout << "b is " << b << std::endl;
}

