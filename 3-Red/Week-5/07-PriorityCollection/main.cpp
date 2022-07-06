/*
 * Реализуйте шаблонный контейнер PriorityCollection, позволяющий хранить
 * объекты некопируемого типа, а также совершать с ними следующие операции:
 * - добавить элемент с нулевым приоритетом;
 * - добавить набор элементов с нулевыми приоритетами;
 * - увеличить на 1 приоритет заданного элемента;
 * - извлечь из контейнера элемент с максимальным приоритетом.
 * Поскольку добавление элемента заключается в его перемещении в контейнер,
 * метод увеличения приоритета не может принимать сам элемент. Поэтому метод,
 * добавляющий элементы, для каждого из них должен вернуть некий идентификатор,
 * который затем можно использовать для вызова других методов.
 *
 * Тип идентификатора — PriorityCollection::Id — вы должны выбрать
 * самостоятельно. Он должен быть легко копируемым: например, числом, указателем
 * или итератором. Примеры определения и использования типа Id вы можете найти в
 * шаблоне решения.
 *
 * Гарантии
 * - Вы можете полагаться на то, что для элементов типа T определены перемещение
 * и сравнение на ==, != и <. Все операции над элементами имеют константную
 * сложность.
 * - Гарантируется, что все добавляемые элементы различны, однако добавленный и
 *   затем извлечённый элемент может быть добавлен вновь.
 * - Методы Get и Promote всегда вызываются от валидных с точки зрения метода
 *   IsValid идентификаторов.
 * - Методы GetMax и PopMax вызываются только при наличии элементов в контейнере.
 * - При наличии нескольких элементов с одинаковым максимальным приоритетом
 *   необходимо выбирать и извлекать тот, который был добавлен позже остальных.
 */
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include <list>
#include <set>

using namespace std;

template<typename T>
class PriorityCollection {
 public:
  using Id = int;

  Id Add(T object);

  template<typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin);

  [[nodiscard]] bool IsValid(Id id) const;

  [[nodiscard]] const T& Get(Id id) const;

  void Promote(Id id);

  [[nodiscard]] std::pair<const T&, int> GetMax() const;

  std::pair<T, int> PopMax();

 private:
  struct ObjectItem {
    T   data;
    int priority = 0;
  };
  static const int none_priority_ = -1;

  std::vector<ObjectItem>      objects_;
  std::set<std::pair<int, Id>> sorted_objects_;
};

template<typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object) {
  const Id new_id = objects_.size();
  objects_.push_back({std::move(object)});
  sorted_objects_.insert({0, new_id});
  return new_id;
}

template<typename T>
template<typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
  while (range_begin != range_end) {
    *ids_begin++ = Add(std::move(*range_begin++));
  }
}

template<typename T>
bool PriorityCollection<T>::IsValid(Id id) const {
  return id >= 0 && id < static_cast<int>(objects_.size()) &&
      objects_[id].priority != none_priority_;
}

template<typename T>
const T& PriorityCollection<T>::Get(Id id) const {
  return objects_[id].data;
}

template<typename T>
void PriorityCollection<T>::Promote(Id id) {
  auto& item = objects_[id];
  const int old_priority = item.priority;
  const int new_priority = ++item.priority;
  sorted_objects_.erase({old_priority, id});
  sorted_objects_.insert({new_priority, id});
}

template<typename T>
std::pair<const T&, int> PriorityCollection<T>::GetMax() const {
  const auto& item = objects_[std::prev(sorted_objects_.end())->second];
  return {item.data, item.priority};
}

template<typename T>
std::pair<T, int> PriorityCollection<T>::PopMax() {
  const auto sorted_objects_it = std::prev(sorted_objects_.end());
  auto& item = objects_[sorted_objects_it->second];
  sorted_objects_.erase(sorted_objects_it);
  const int priority = item.priority;
  item.priority = none_priority_;
  return {std::move(item.data), priority};
}

class StringNonCopyable : public string {
 public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;

  const auto white_id  = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id    = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
}

