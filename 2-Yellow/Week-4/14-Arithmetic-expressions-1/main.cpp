/*
 * Реализуйте построение арифметического выражения согласно следующей схеме:
 * - изначально есть выражение, состоящее из некоторого целого числа x;
 * - на каждом шаге к текущему выражению применяется некоторая операция:
 *   прибавление числа, вычитание числа, умножение на число или деление на
 *   число; перед применением операции выражение всегда должно быть заключено в
 *   скобки.
 *
 * Формат ввода:
 * В первой строке содержится исходное целое число x. Во второй строке
 * содержится целое неотрицательное число N — количество операций. В каждой из
 * следующих N строк содержится очередная операция:
 * - прибавление числа a: + a;
 * - либо вычитание числа b: - b;
 * - либо умножение на число c: * c;
 * - либо деление на число d: / d.
 *
 * Количество операций может быть нулевым — в этом случае необходимо вывести
 * исходное число.
 *
 * Формат вывода:
 * Выведите единственную строку — построенное арифметическое выражение.
 * Обратите внимание на расстановку пробелов вокруг символов:
 * - каждый символ бинарной операции (+, -, * или /) должен быть окружён ровно
 *   одним пробелом с каждой стороны: (8) * 3;
 * - символ унарного минуса (для отрицательных чисел) не нуждается в
 *   дополнительном пробеле: -5;
 * - скобки и числа не нуждаются в дополнительных пробелах.
 */
#include <iostream>
#include <deque>

using namespace std;

void AddBrackets(deque<char>& expr) {
  expr.push_front('(');
  expr.push_back(')');
}

void AddOperation(deque<char>& expr, char op) {
  expr.push_back(' ');
  expr.push_back(op);
  expr.push_back(' ');
}

void AddValue(deque<char>& expr, int v) {
  for (char c : to_string(v)) {
    expr.push_back(c);
  }
}

int main() {
  int first_number;
  cin >> first_number;

  string tmp = to_string(first_number);

  deque<char> expression{tmp.begin(), tmp.end()};

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    AddBrackets(expression);

    char operation;
    cin >> operation;
    AddOperation(expression, operation);

    int value;
    cin >> value;
    AddValue(expression, value);
  }
  for (char c : expression) {
    cout << c;
  }
}