/*
 * Напишите функцию FindStartsWith:
 * - принимающую отсортированный набор строк в виде итераторов range_begin,
 *   range_end и один символ prefix;
 * - возвращающую диапазон строк, начинающихся с символа prefix, в виде пары
 *   итераторов.
 *
 * Если итоговый диапазон пуст, его границы должны указывать на то место в
 * контейнере, куда можно без нарушения порядка сортировки вставить любую
 * строку, начинающуюся с символа prefix (подобно алгоритму equal_range).
 *
 * Гарантируется, что строки состоят лишь из строчных латинских букв и символ
 * prefix также является строчной латинской буквой.
 *
 * Поиск должен осуществляться за логарифмическую сложность — например, с
 * помощью двоичного поиска.
 *
 * Подсказка
 * К символам (char) можно прибавлять или вычитать числа, получая таким образом
 * следующие или предыдущие буквы в алфавитном порядке. Например, для строки s
 * выражение --s[0] заменит её первую букву на предыдущую.
 *
 * Обратите внимание, что выражение 'a' + 1 имеет тип int и поэтому может
 * понадобиться привести его к типу char с помощью static_cast.
 */
#include <iostream>
#include <vector>

using namespace std;

struct Comp {
  bool operator()(const string& s, const char& prefix) {
    return s.front() < prefix;
  }
  bool operator()(const char& prefix, const string& s) {
    return prefix < s.front();
  }
};

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix) {
  return equal_range(range_begin, range_end, prefix, Comp());
}

int main() {
  const vector<string> kSortedStrings = {"moscow", "murmansk", "vologda"};

  const auto kMResult =
      FindStartsWith(begin(kSortedStrings), end(kSortedStrings), 'm');
  for (auto it = kMResult.first; it != kMResult.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto kPResult =
      FindStartsWith(begin(kSortedStrings), end(kSortedStrings), 'p');
  cout << (kPResult.first - begin(kSortedStrings)) << " " <<
       (kPResult.second - begin(kSortedStrings)) << endl;

  const auto kZResult =
      FindStartsWith(begin(kSortedStrings), end(kSortedStrings), 'z');
  cout << (kZResult.first - begin(kSortedStrings)) << " " <<
       (kZResult.second - begin(kSortedStrings)) << endl;
}
