/*
 * На практике часто возникают объекты, создание которых занимает значительное
 * время, например, потоки (threads), TCP-соединения или подключения к базе
 * данных. Поэтому, когда такой объект становится не нужен, его не разрушают, а
 * откладывают в сторону, чтобы потом переиспользовать. В этой задаче вам
 * предстоит реализовать такую схему — вам надо написать шаблон класса
 * ObjectPool.
 * - Объект класса ObjectPool должен поддерживать два набора объектов:
 *   выделенные и освобождённые, — изначально оба набора пусты.
 * - Метод Allocate должен работать так:
 *   1. если есть хотя бы один освобождённый объект, то его надо перенести в
 *      множество выделенных и вернуть указатель на него в качестве результата
 *      функции
 *   2. если же освобождённых объектов нет, то создаётся новый объект,
 *      помещается в множество выделенных, и указатель на него возвращается в
 *      качестве результата функции
 * - Метод TryAllocate работает аналогично, однако если освобождённых объектов
 *   нет, он должен просто возвращать nullptr.
 * - Метод Deallocate переносит объект из множества выделенных в множество
 *   освобождённых; если переданный объект не содержится в множестве выделенных,
 *   метод Deallocate должен бросать исключение invalid_argument.
 * - Методы Allocate и TryAllocate должны возвращать объекты в порядке FIFO,
 *   т.е. множество освобождённых объектов должно представлять собой очередь:
 *   методы [Try]Allocate должны извлекать объекты из её начала, а метод
 *   Deallocate должен помещать освобождаемый объект в её конец.
 * - Деструктор объекта ObjectPool должен уничтожать все объекты пула, как
 *   выделенные, так и освобождённые.
 */
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <set>

using namespace std;

template<class T>
class ObjectPool {
 public:
  T* Allocate() {
    T* ptr;
    if (!deallocated_.empty()) {
      ptr = *allocated_.insert(deallocated_.front()).first;
      deallocated_.pop();
    } else {
      ptr = *allocated_.insert(new T).first;
    }
    return ptr;
  }
  T* TryAllocate() {
    if (deallocated_.empty()) {
      return nullptr;
    }
    return Allocate();
  }

  void Deallocate(T* object) {
    if (!allocated_.erase(object)) {
      throw invalid_argument("Unable to deallocate object that not exist");
    }
    deallocated_.push(object);
  }

  ~ObjectPool() {
    for (auto& object : allocated_) {
      delete object;
    }

    while (!deallocated_.empty()) {
      delete deallocated_.front();
      deallocated_.pop();
    }
  }

 private:
  set<T*>   allocated_;
  queue<T*> deallocated_;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p_1 = pool.Allocate();
  auto p_2 = pool.Allocate();
  auto p_3 = pool.Allocate();

  *p_1 = "first";
  *p_2 = "second";
  *p_3 = "third";

  pool.Deallocate(p_2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p_3);
  pool.Deallocate(p_1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p_1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
}
