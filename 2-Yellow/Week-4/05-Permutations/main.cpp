/*
 * Дано целое положительное число N, не превышающее 9. Выведите все перестановки
 * чисел от 1 до N в обратном лексикографическом порядке.
 *
 * Ввод:
 * 3
 *
 * Вывод:
 * 3 2 1
 * 3 1 2
 * 2 3 1
 * 2 1 3
 * 1 3 2
 * 1 2 3
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> permutations(n);
  iota(permutations.rbegin(), permutations.rend(), 1);

  auto print = [permutations]() {
    for (int i : permutations) {
      cout << i << " ";
    }
    cout << endl;
  };

  for (int i = 0; i < tgamma(n + 1); ++i) {
    print();
    prev_permutation(permutations.begin(), permutations.end());
  }
}
