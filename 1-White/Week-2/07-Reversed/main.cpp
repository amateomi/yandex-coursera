/*
 * Реализуйте функцию vector<int> Reversed(const vector<int>& v), возвращающую
 * копию вектора v, в которой числа переставлены в обратном порядке.
 *
 * Гарантируется, что вектор v имеет ненулевую длину.
 */
#include <iostream>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v) {
  vector<int> result;
  for (size_t i = v.size(); i > 0; --i) {
    result.push_back(v[i - 1]);
  }
  return result;
}

int main() {
  auto res = Reversed({1, 5, 3, 4, 2});
  for (auto i : res) {
    cout << i << ' ';
  }
}
