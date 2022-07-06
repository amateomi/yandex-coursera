/*
 * В файле input.txt записаны вещественные числа, по одному на строчку. На
 * стандартный вывод напечатайте эти числа в том же порядке, по одному на
 * строке, но сделайте так, чтобы у каждого из них было ровно три знака после
 * десятичной точки.
 */
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
  ifstream file("input.txt");
  if (file) {
    double number;
    cout << fixed << setprecision(3);
    while (file >> number) {
      cout << number << endl;
    }
  }
}
