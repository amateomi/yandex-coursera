/*
 * Напишите шаблонную функцию MergeSort, принимающую два итератора шаблонного
 * типа RandomIt и сортирующую заданный ими диапазон с помощью сортировки
 * слиянием. Гарантируется, что:
 * - итераторы типа RandomIt аналогичны по функциональности итераторам вектора и
 *   строки, то есть их можно сравнивать с помощью операторов <, <=, > и >=, а
 *   также вычитать и складывать с числами;
 * - сортируемые объекты можно сравнивать с помощью оператора <.
 *
 * Алгоритм
 * Классический алгоритм сортировки слиянием выглядит следующим образом:
 * 1. Если диапазон содержит меньше 2 элементов, выйти из функции.
 * 2. Создать вектор, содержащий все элементы текущего диапазона.
 * 3. Разбить вектор на две равные части. (В этой задаче гарантируется, что
 *    длина передаваемого диапазона является степенью двойки, так что вектор
 *    всегда можно разбить на две равные части.)
 * 4. Вызвать функцию MergeSort от каждой половины вектора.
 * 5. С помощью алгоритма std::merge слить отсортированные половины, записав
 *    полученный отсортированный диапазон вместо исходного.
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
  auto middle = elements.begin();
  advance(middle, dist / 2);

  MergeSort(elements.begin(), middle);
  MergeSort(middle, elements.end());

  merge(elements.begin(), middle,
        middle, elements.end(),
        range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
}
