/*
 * Условие
 * В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел. Первым
 * числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив
 * A. Между собой числа разделены пробелом.
 * Отсортируйте массив А по модулю и выведите его в стандартный поток.
 *
 * Ограничения
 * - 0 <= N <= 1000
 * - -1000000 <= A[i] <= 1000000
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (auto& i : a) {
    cin >> i;
  }

  sort(begin(a), end(a), [](int x, int y) -> bool { return abs(x) < abs(y); });

  for (const auto& i : a) {
    cout << i << ' ';
  }
}
