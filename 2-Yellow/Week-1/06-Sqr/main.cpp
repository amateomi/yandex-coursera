/*
 * Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и
 * для контейнеров. Функция должна возвращать копию исходного контейнера,
 * модифицировав его следующим образом:
 * - для vector элементы нужно возвести в квадрат;
 * - для map в квадрат нужно возвести только значения, но не ключи;
 * - для pair в квадрат нужно возвести каждый элемент пары.
 *
 * Функция должна корректно работать не только для контейнеров, состоящих из
 * чисел, но и для составных объектов, например, векторов словарей пар чисел.
 *
 * Для успешной сдачи решения необходимо сделать предварительное объявление
 * шаблонных функций перед всеми шаблонными функциями.
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<typename T>
T Sqr(T value);

template<typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> p);

template<typename T>
vector<T> Sqr(vector<T> v);

template<typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> m);

template<typename T>
T Sqr(T value) {
  return value * value;
}

template<typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> p) {
  return {Sqr(p.first), Sqr(p.second)};
}

template<typename T>
vector<T> Sqr(vector<T> v) {
  vector<T> new_vector;
  new_vector.reserve(v.size());
  for (const auto& value : v) {
    new_vector.push_back(Sqr(value));
  }
  return new_vector;
}

template<typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> m) {
  map<Key, Value> new_map;
  for (const auto&[kKey, kValue] : m) {
    new_map[kKey] = Sqr(kValue);
  }
  return new_map;
}

int main() {
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
}
