/*
 * =====================================================================================
 *
 *       Filename:  BitField.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>

struct S {
  // three-bit unsigned field,
  // allowed values are 0...7
  unsigned int b : 3;
};

struct S2 {
  unsigned int b : 3;
  unsigned int c : 3;
};



struct S3 {
    // will usually occupy 2 bytes:
    // 3 bits: value of b1
    // 2 bits: unused
    // 6 bits: value of b2
    // 2 bits: value of b3
    // 3 bits: unused
    unsigned char b1 : 3, : 2, b2 : 6, b3 : 2;
};



struct S4 {
    // will usually occupy 2 bytes:
    // 3 bits: value of b1
    // 5 bits: unused
    // 6 bits: value of b2
    // 2 bits: value of b3
    unsigned char b1 : 3;
    unsigned char :0; // start a new byte
    unsigned char b2 : 6;
    unsigned char b3 : 2;
};

int main(int, char**) {
  S s = {7};
  ++s.b;                     // unsigned overflow (guaranteed wrap-around)
  std::cout << s.b << '\n';  // output: 0
  S2 ss = {7, 0};
  std::cout << ss.b << " " << ss.c << std::endl;
	++ss.b;
  std::cout << ss.b << " " << ss.c << std::endl;
	ss.c = 7;
  std::cout << ss.b << " " << ss.c << std::endl;
	++ss.c;
  std::cout << ss.b << " " << ss.c << std::endl;
}

