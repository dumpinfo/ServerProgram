/*
 * =====================================================================================
 *
 *       Filename:  ExceptionKnowledge.cpp
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
#include <stdexcept>

template <typename T>
class Stack {
 public:
  // 是不是异常安全的呢
  Stack() : m_data(0), m_capacity(20), m_used(0) { m_data = new T[m_capacity]; }
  // 是不是异常安全的呢
  ~Stack() { delete[] m_data; }
  // exception safe?
  int size() const { return m_used; }
  // push object exception safe?
  void push(const T& t) {
    if (m_used >= m_capacity) {
      T* data = newCopy(m_data, m_capacity, m_capacity * 2);
      delete[] m_data;
      m_data = data;
      m_capacity *= 2;
    }

    // the next two line can change to m_data[++m_used] = t;
    m_data[m_used + 1] = t;
    ++m_used;
  }

  // we have bad news for this version
  T pop() {
    if (m_used == 0) {
      throw std::runtime_error("empty, bad");
    }
    T obj = m_data[m_used - 1];
    --m_used;
    return obj;
  }

	// we have bad news for this version
  void pop(T& object) {
    if (m_used == 0) {
      throw std::runtime_error("empty, bad");
    }
    object = m_data[m_used - 1];
    --m_used;
  }

	// we have bad news for this version ????? not so bad
  T& top() {
    if (m_used == 0) {
      throw std::runtime_error("empty, bad");
    }
    return m_data[m_used - 1];
  }

	void popTop() {
    if (m_used == 0) {
      throw std::runtime_error("empty, bad");
    }
		--m_used;
	}

 private:
  T* m_data;
  int m_capacity;
  int m_used;
  T* newCopy(const T* old, int oldSize, int newSize) {
    assert(newSize > oldSize);
    T* data = new T[newSize];
    try {
      std::copy(old, old + oldSize, data);
    } catch (...) {
      delete[] data;
      throw;
    }
    return data;
  }

	// T
	// 基本异常保证
	// 强异常保证
	// 无异常
	// 为什么说析构函数抛出异常是邪恶的？？？？
};

// Stack<T> ok???
// no has very big problems
class SomeObject {
};

static void versionOne() {
	Stack<SomeObject> s; // is it exception safe?
}


class Person {
	public:
};

static void exceptionPoint() {
}

int main(int argc, char** argv) {
	versionOne();
	//exceptionPoint();

}

