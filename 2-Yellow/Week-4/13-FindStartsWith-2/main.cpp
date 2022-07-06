/*
 * Напишите более универсальный вариант функции FindStartsWith, принимающий в
 * качестве префикса произвольную строку, состоящую из строчных латинских букв.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix) {

  auto left = lower_bound(
      range_begin, range_end, prefix,
      [](const string& s, const string& prefix) {
        return s.substr(0, prefix.size()) < prefix;
      });

  if (left == range_end) {
    auto iter = lower_bound(range_begin, range_end, prefix);
    return {iter, iter};
  }

  auto right = upper_bound(
      range_begin, range_end, prefix,
      [](const string& prefix, const string& s) {
        return prefix < s.substr(0, prefix.size());
      });

  return {left, right};
}

int main() {
  const vector<string> kSortedStrings = {"moscow", "motovilikha", "murmansk"};

  const auto kMoResult =
      FindStartsWith(begin(kSortedStrings), end(kSortedStrings), "mo");
  for (auto it = kMoResult.first; it != kMoResult.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto kMtResult =
      FindStartsWith(begin(kSortedStrings), end(kSortedStrings), "mt");
  cout << (kMtResult.first - begin(kSortedStrings)) << " " <<
       (kMtResult.second - begin(kSortedStrings)) << endl;

  const auto kNaResult =
      FindStartsWith(begin(kSortedStrings), end(kSortedStrings), "na");
  cout << (kNaResult.first - begin(kSortedStrings)) << " " <<
       (kNaResult.second - begin(kSortedStrings)) << endl;
}
