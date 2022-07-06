/*
 * Напишите шаблонную функцию FindGreaterElements, принимающую множество
 * elements объектов типа T и ещё один объект border типа T и возвращающую
 * вектор из всех элементов множества, бо́льших border, в возрастающем порядке.
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

template<typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
  return {find_if(elements.begin(), elements.end(),
                  [border](const T& value) {
                    return value > border;
                  }),
          elements.end()};
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;

  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
}
