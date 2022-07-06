/*
 * Условие
 * В стандартном потоке дана одна строка, состоящая из числа N и следующих за
 * ним N строк S. Между собой число и строки разделены пробелом.
 * Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя
 * регистр букв, и выведите их в стандартный поток вывода.
 *
 * Ограничения
 * - 0 <= N <= 1000
 * - 1 <= |S| <= 15
 * - Каждая строка S[i] может состоять из следующих символов: [0-9,a-z,A-Z]
 */
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<string> v(n);
  for (auto& i : v) {
    cin >> i;
  }

  sort(begin(v), end(v),
       [](const string& x, const string& y) {
         return lexicographical_compare(
             begin(x), end(x),
             begin(y), end(y),
             [](char x, char y) { return tolower(x) < tolower(y); });
       }
  );

  for (const auto& i : v) {
    cout << i << ' ';
  }
}
