/*
 * Напишите функцию FindNearestElement, для множества целых чисел numbers и
 * данного числа border возвращающую итератор на элемент множества, ближайший к
 * border. Если ближайших элементов несколько, верните итератор на наименьший из
 * них.
 */
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {
  auto first_iter = numbers.lower_bound(border);

  if (first_iter == numbers.begin()) {
    return first_iter;
  }
  if (first_iter == numbers.end()) {
    return prev(first_iter);
  }

  auto second_iter = prev(first_iter);

  auto first_diff = *first_iter - border;
  auto second_diff = border - *second_iter;

  return first_diff < second_diff ? first_iter : second_iter;
}

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
       *FindNearestElement(numbers, 0) << " " <<
       *FindNearestElement(numbers, 3) << " " <<
       *FindNearestElement(numbers, 5) << " " <<
       *FindNearestElement(numbers, 6) << " " <<
       *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
}
