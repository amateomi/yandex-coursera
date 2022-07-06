/*
 * Напишите функцию SplitIntoWords, разбивающую строку на слова по пробелам.
 *
 * Гарантируется, что:
 * строка непуста;
 * строка состоит лишь из латинских букв и пробелов;
 * первый и последний символы строки не являются пробелами;
 * строка не содержит двух пробелов подряд.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
  vector<string> result;
  auto word_begin = s.begin();
  while (true) {
    auto word_end = find(word_begin, s.end(), ' ');
    result.emplace_back(word_begin, word_end);
    if (word_end == s.end()) {
      break;
    }
    word_begin = ++word_end;
  }
  return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

}
