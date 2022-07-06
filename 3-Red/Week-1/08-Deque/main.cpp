/*
 * Напишите шаблонный класс Deque, содержащий следующий набор методов:
 * - конструктор по умолчанию;
 * - константный метод Empty, возвращающий true, если дек не содержит ни одного
 *   элемента;
 * - константный метод Size, возвращающий количество элементов в деке;
 * - T& operator[](size_t index) и const T& operator[](size_t index) const;
 * - константный и неконстантный метод At(size_t index), генерирующий
 *   стандартное исключение out_of_range, если индекс больше или равен
 *   количеству элементов в деке;
 * - константные и неконстантные версии методов Front и Back, возвращающих
 *   ссылки на первый и последний элемент дека соответственно;
 * - методы PushFront и PushBack.
 *
 * Неконстантные версии методов должны позволять изменять соответствующий
 * элемент дека.
 *
 * Для реализации заведите внутри класса Deque два вектора: в один осуществляйте
 * вставку в методе PushFront, а в другой — в методе PushBack.
 */
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class Deque {
 public:
  Deque() = default;

  [[nodiscard]]
  bool Empty() const { return front_.empty() && back_.empty(); };

  [[nodiscard]]
  size_t Size() const { return front_.size() + back_.size(); }

  T& operator[](size_t index) {
    if (index < front_.size()) {
      return front_[front_.size() - 1 - index];
    } else {
      return back_[index - front_.size()];
    }
  }
  const T& operator[](size_t index) const {
    if (index < front_.size()) {
      return front_[front_.size() - 1 - index];
    } else {
      return back_[index - front_.size()];
    }
  }

  T& At(size_t index) {
    if (index < front_.size()) {
      return front_[front_.size() - 1 - index];
    } else if (index - front_.size() < back_.size()) {
      return back_[index - front_.size()];
    } else {
      throw out_of_range("Out of range");
    }
  }
  [[nodiscard]] const T& At(size_t index) const {
    if (index < front_.size()) {
      return front_[front_.size() - 1 - index];
    } else if (index - front_.size() < back_.size()) {
      return back_[index - front_.size()];
    } else {
      throw out_of_range("Out of range");
    }
  }

  T& Front() {
    return !front_.empty() ? front_.back()
                           : back_.front();
  }
  [[nodiscard]] const T& Front() const {
    return !front_.empty() ? front_.back()
                           : back_.front();
  }
  T& Back() {
    return !back_.empty() ? back_.back()
                          : front_.front();
  }
  [[nodiscard]] const T& Back() const {
    return !back_.empty() ? back_.back()
                          : front_.front();
  }

  void PushFront(const T& value) { front_.push_back(value); }
  void PushBack(const T& value) { back_.push_back(value); }

 private:
  vector<T> front_;
  vector<T> back_;
};

int main() {
  Deque<int> deque;
  deque.PushFront(3);
  deque.PushFront(4);
  deque.PushFront(5);
  deque.PushFront(6);
  cout << deque.Back() << endl;
}
