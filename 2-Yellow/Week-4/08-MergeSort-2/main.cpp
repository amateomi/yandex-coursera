/*
 * Реализуйте сортировку слиянием, разбивая диапазон на 3 равные части, а не на
 * 2. Гарантируется, что длина исходного диапазона является степенью 3.
 *
 * Соответственно, пункты 3–5 алгоритма нужно заменить следующими:
 * - Разбить вектор на 3 равные части.
 * - Вызвать функцию MergeSort от каждой части вектора.
 * - Слить первые две трети вектора с помощью алгоритма merge, сохранив
 * результат во временный вектор с помощью back_inserter.
 * - Слить временный вектор из предыдущего пункта с последней третью вектора из
 * п. 2, записав полученный отсортированный диапазон вместо исходного.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  auto dist = distance(range_begin, range_end);
  if (dist < 2) {
    return;
  }
  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  auto left_border = elements.begin();
  advance(left_border, dist / 3);

  auto right_border = left_border;
  advance(right_border, dist / 3);

  MergeSort(elements.begin(), left_border);
  MergeSort(left_border, right_border);
  MergeSort(right_border, elements.end());

  vector<typename RandomIt::value_type> tmp;

  merge(elements.begin(), left_border,
        left_border, right_border,
        back_inserter(tmp));

  merge(tmp.begin(), tmp.end(),
        right_border, elements.end(),
        range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
}
