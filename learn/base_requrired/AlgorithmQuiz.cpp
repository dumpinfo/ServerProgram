/*
 * =====================================================================================
 *
 *       Filename:  AlgorithmQuiz.cpp
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
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>
#include <queue>
#include <vector>

int rerangeOrder(std::vector<int>& arr, int v) {
	auto iter = std::partition(arr.begin(), arr.end(), [v](int d) { return d < v;});
	return std::distance(arr.begin(), iter);
}

void testBound() {
  std::vector<int> v = {1, 2, 2, 3, 4, 4, 6, 6, 7};
  auto iter = std::lower_bound(v.begin(), v.end(), 4);
  auto e = std::upper_bound(v.begin(), v.end(), 4);
  std::copy(iter, e, std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
  auto b = std::lower_bound(v.begin(), v.end(), 5);
	e = std::upper_bound(v.begin(), v.end(), 5);
  std::copy(b, e, std::ostream_iterator<int>(std::cout, " "));
	std::cout << "dist " << std::distance(b, v.end()) << "\n";
	std::cout << "dist " << std::distance(e, v.end()) << "\n";

}

using TopGroup = std::priority_queue<int>;
void consumeTopGroup(TopGroup& g) {
	while(!g.empty()) {
		std::cout << g.top() << " ";
		g.pop();
	}
	std::cout << std::endl;
}

void alwaysTopOne() {
	TopGroup topGroup;
	for(auto v : {3,4,5,2,4,1,4,11})
		topGroup.push(v);
	consumeTopGroup(topGroup);

}

int main() {
	alwaysTopOne();
	//testBound();
//	std::vector<int> arr = { 10, 2, 3, 4, 11, 2, 13, 7};
//	std::cout << "before: ";
//	for(auto& v : arr) std::cout << v << " ";
//	std::cout << "\n";
//	auto d = rerangeOrder(arr, 7);
//	std::cout << "after: ";
//	for(auto& v : arr) std::cout << v << " ";
//	std::cout << "\n";
//	std::cout << "distance " << d << "\n";
}

