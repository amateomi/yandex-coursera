/*
 * Реализуйте функцию void Reverse(vector<int>& v), которая переставляет
 * элементы вектора в обратном порядке.
 *
 * Гарантируется, что вектор v имеет ненулевую длину.
 */
#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector<int>& v) {
  for (size_t i = 0; i < v.size() / 2; ++i) {
    swap(v[i], v[v.size() - 1 - i]);
  }
}

int main() {
  vector<int> numbers = {1, 5, 3, 4, 2};
  Reverse(numbers);
  for (auto i : numbers) {
    cout << i << ' ';
  }
}
