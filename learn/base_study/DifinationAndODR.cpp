/*
 * =====================================================================================
 *
 *       Filename:  DifinationAndODR.cpp
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
extern  int a; // declares, but doesn't define a
extern const int b = 1; // defines b
int f(int); // declares, but doesn't define f
int f(int x); // declares, but doesn't define f and x
int f(int x) { // defines f and x
     return x+a;
}
struct S {    // defines S
    int n;        // defines S::n
    static int i; // declares, but doesn't define S::i
};
int S::i; // defines S::i
struct S; // declares, but doesn't define S
class Y f(class T p); // declares, but doesn't define Y and T (and also f and p)
template<typename T> // declares, but doesn't define T
template<> struct A<int>; // declares, but doesn't define A<int>
typedef S S2; // declares, but doesn't define S2 (S may be incomplete)
