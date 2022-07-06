/*
 * Напишите функцию PrintVectorPart, принимающую вектор целых чисел numbers,
 * выполняющую поиск первого отрицательного числа в нём и выводящую в
 * стандартный вывод все числа, расположенные левее найденного, в обратном
 * порядке. Если вектор не содержит отрицательных чисел, выведите все числа в
 * обратном порядке.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
  auto it = find_if(numbers.begin(), numbers.end(),
                    [](int n) {
                      return n < 0;
                    });
  while (it != numbers.begin()) {
    --it;
    cout << *it << " ";
  }
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
}
