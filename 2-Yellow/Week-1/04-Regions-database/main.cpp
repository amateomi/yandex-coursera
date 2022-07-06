/*
 * Имеется база регионов, представленная вектором структур Region:
 *
 * struct Region {
 *   string std_name;
 *   string parent_std_name;
 *   map<Lang, string> names;
 *   int64_t population;
 * };
 *
 * Здесь Lang — идентификатор языка:
 *
 * enum class Lang {
 *   DE, FR, IT
 * };
 *
 * Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и
 * определяющую, какое максимальное количество повторов (число вхождений одного
 * и того же элемента) она содержит. Две записи (объекты типа Region) считаются
 * различными, если они отличаются хотя бы одним полем.
 *
 * int FindMaxRepetitionCount(const vector<Region>& regions);
 *
 * Если все записи уникальны, считайте максимальное количество повторов равным
 * 1. Если записи отсутствуют, верните 0. Гарантируется, что типа int достаточно
 * для хранения ответа.
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

bool operator<(const Region& lhs, const Region& rhs) {
  return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population)
      < tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
  int result = 0;
  map<Region, int> repetition_count;
  for (const auto& region : regions) {
    result = max(result, ++repetition_count[region]);
  }
  return result;
}
