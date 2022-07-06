/*
 * Реализуйте шаблонную функцию возвращающую итератор на максимальный элемент в
 * диапазоне [first, last), для которого предикат pred возвращает true. Если
 * диапазон содержит несколько подходящих элементов с максимальным значением, то
 * результатом будет первое вхождение такого элемента. Если диапазон не содержит
 * подходящих элементов, то функция должна вернуть last.
 *
 * Гарантируется, что:
 * - pred принимает аргумент того типа, который имеют элементы диапазона
 * - для ForwardIterator определены операторы ++, ==, !=, * (разыменование)
 * - для типа, на который указывает итератор, определён оператор < («меньше»)
 */
#include "test_runner.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>

using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first,
                               ForwardIterator last,
                               UnaryPredicate pred) {
  // Find first matched element
  auto max_element = find_if(first, last, pred);
  if (max_element == last) {
    return last;
  }
  for (auto iter = find_if(next(max_element), last, pred);
       iter != last;
       iter = find_if(next(iter), last, pred)) {
    if (*iter > *max_element) {
      max_element = iter;
    }
  }
  return max_element;
}

void TestUniqueMax() {
  auto is_even = [](int x) {
    return x % 2 == 0;
  };

  const list<int> hill{2, 4, 8, 9, 6, 4, 2};
  auto max_iterator = hill.begin();
  advance(max_iterator, 2);

  vector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  Assert(
      max_element_if(numbers.begin(), numbers.end(), is_even) == --numbers.end(),
      "Expect the last element"
  );
  Assert(
      max_element_if(hill.begin(), hill.end(), is_even) == max_iterator,
      "Expect the maximal even number"
  );
}

void TestSeveralMax() {
  struct IsCapitalized {
    bool operator()(const string& s) {
      return !s.empty() && isupper(s.front());
    }
  };

  const forward_list<string> text{"One", "two", "Three", "One", "Two",
                                  "Three", "one", "Two", "three"};
  auto max_iterator = text.begin();
  advance(max_iterator, 4);

  Assert(
      max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
      "Expect the first \"Two\""
  );
}

void TestNoMax() {
  const vector<int> empty;
  const string str = "Non-empty string";

  auto always_true = [](int) {
    return true;
  };
  Assert(
      max_element_if(empty.begin(), empty.end(), always_true) == empty.end(),
      "Expect end for empty container"
  );

  auto always_false = [](char) {
    return false;
  };
  Assert(
      max_element_if(str.begin(), str.end(), always_false) == str.end(),
      "Expect end for AlwaysFalse predicate"
  );
}

int main() {
  TestRunner tr;
  tr.RunTest(TestUniqueMax, "TestUniqueMax");
  tr.RunTest(TestSeveralMax, "TestSeveralMax");
  tr.RunTest(TestNoMax, "TestNoMax");
  return 0;
}