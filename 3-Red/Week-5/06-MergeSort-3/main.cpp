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
 * В этой задаче вы должны реализовать точь-в-точь алгоритм, представленный
 * ниже; тестирующая система будет проверять, что вы выполняете с элементами
 * именно эти действия:
 * - Если диапазон содержит меньше 2 элементов, выйти из функции.
 * - Создать вектор, содержащий все элементы текущего диапазона.
 * - Разбить вектор на три равные части. (В этой задаче гарантируется, что длина
 *   передаваемого диапазона является степенью тройки, так что вектор всегда
 *   можно разбить на три равные части.)
 * - Вызвать функцию MergeSort от каждой части вектора.
 * - Слить первые две трети вектора с помощью алгоритма merge, сохранив
 *   результат во временный вектор с помощью back_inserter.
 * - Слить временный вектор из предыдущего пункта с последней третью вектора из
 *   п. 2, записав полученный отсортированный диапазон вместо исходного.
 */
#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  auto dist = distance(range_begin, range_end);
  if (dist < 2) {
    return;
  }
  vector<typename RandomIt::value_type> elements{
      make_move_iterator(range_begin),
      make_move_iterator(range_end)
  };

  auto left_border = elements.begin();
  advance(left_border, dist / 3);

  auto right_border = left_border;
  advance(right_border, dist / 3);

  MergeSort(elements.begin(), left_border);
  MergeSort(left_border, right_border);
  MergeSort(right_border, elements.end());

  vector<typename RandomIt::value_type> tmp;
  merge(make_move_iterator(elements.begin()), make_move_iterator(left_border),
        make_move_iterator(left_border), make_move_iterator(right_border),
        back_inserter(tmp));

  merge(make_move_iterator(tmp.begin()), make_move_iterator(tmp.end()),
        make_move_iterator(right_border), make_move_iterator(elements.end()),
        range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)))
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
