/*
 * Дан набор строк. Необходимо разбить их на группы, в каждой из которых все
 * строки имеют одинаковый набор символов.
 * Например, если даны строки law, port, top, laptop, pot, paloalto, wall, awl,
 * нужно разбить их на 4 группы:
 * - строки, состоящие только из букв a, l и w: law, wall, awl;
 * - строки, состоящие только из букв o, p, r и t: port;
 * - строки, состоящие только из букв o, p и t: top, pot;
 * - строки, состоящие только из букв a, l, o, p, t: laptop, paloalto.
 */
#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

template<typename String>
using Group = vector<String>;

template<typename String>
using Char = typename String::value_type;

template<typename String>
String GetKey(const String& string) {
  String key = string;
  sort(key.begin(), key.end());
  key.erase(unique(key.begin(), key.end()), key.end());
  return key;
}

template<typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  map<String, Group<String>> groups_map;
  for (String& s : strings) {
    groups_map[GetKey(s)].push_back(move(s));
  }

  vector<Group<String>> groups;
  for (auto&[_, g] : groups_map) {
    groups.push_back(move(g));
  }

  return groups;
}

void TestGroupingAbc() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto           groups  = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto           groups  = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingAbc);
  RUN_TEST(tr, TestGroupingReal);
}

