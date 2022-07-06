/*
 * Дан набор строк. Найдите количество уникальных строк в этом наборе.
 *
 * Формат ввода:
 * Сначала вводится количество строк N, затем — сами N строк, разделённые
 * символом перевода строки. Все строки состоят лишь из латинских букв, цифр и
 * символов подчёркивания.
 *
 * Формат вывода:
 * Выведите единственное целое число — количество уникальных строк в данном
 * наборе.
 */
#include <iostream>
#include <set>

using namespace std;

int main() {
  set<string> unique_strings;

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string new_string;
    cin >> new_string;
    unique_strings.insert(new_string);
  }
  cout << unique_strings.size();
}
