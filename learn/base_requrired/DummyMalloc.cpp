/*
 * =====================================================================================
 *
 *       Filename:  DummyMalloc.cpp
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
#include <stdlib.h>
#include <cstdio>
#include <cstring>

void dummyMalloc(char* p) {
	p = (char*)malloc(8);
}

int main(int, char**) {
  char str[] = "Hello world";
  dummyMalloc(str);
  strcpy(str, "Hi World\n");
  auto n = printf(str);
}

