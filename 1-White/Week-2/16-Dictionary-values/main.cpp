/*
 * Напишите функцию BuildMapValuesSet, принимающую на вход словарь
 * map<int, string> и возвращающую множество значений этого словаря.
 */
#include <iostream>
#include <map>
#include <set>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
  set<string> result;
  for (auto[key, value] : m) {
    result.insert(value);
  }
  return result;
}