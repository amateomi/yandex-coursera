/*
 * Модифицируйте решение предыдущей части так, чтобы предыдущее выражение
 * обрамлялось скобками лишь при необходимости, то есть только в том случае,
 * когда очередная операция имеет бо́льший приоритет, чем предыдущая.
 */
#include <iostream>
#include <deque>

using namespace std;

bool IsNecessaryBrackets(char next_op) {
  static char last_operation;

  bool is_necessary = (next_op == '*' || next_op == '/')
      && (last_operation == '+' || last_operation == '-');

  last_operation = next_op;

  return is_necessary;
}

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
    char operation;
    cin >> operation;

    if (IsNecessaryBrackets(operation)) {
      AddBrackets(expression);
    }
    AddOperation(expression, operation);

    int value;
    cin >> value;
    AddValue(expression, value);
  }
  for (char c : expression) {
    cout << c;
  }
}
