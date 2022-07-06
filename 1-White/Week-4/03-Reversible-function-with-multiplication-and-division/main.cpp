/*
 * Добавьте в класс Function из задачи «Обратимая функция» обработку умножения
 * ('*') и деления ('/'). Гарантируется отсутствие элементарных операций
 * умножения и деления на 0.
 */
#include <algorithm>
#include <vector>

using namespace std;

class FunctionPart {
 public:
  FunctionPart(char operation, double value) {
    operation_ = operation;
    value_ = value;
  }

  [[nodiscard]]
  double Apply(double source_value) const {
    switch (operation_) {
      case '+':return source_value + value_;
      case '-':return source_value - value_;
      case '*':return source_value * value_;
      case '/':return source_value / value_;
      default:return {};
    }
  }

  void Invert() {
    switch (operation_) {
      case '+':operation_ = '-';
        break;
      case '-':operation_ = '+';
        break;
      case '*':operation_ = '/';
        break;
      case '/':operation_ = '*';
        break;
    }
  }

 private:
  char operation_;
  double value_;
};

class Function {
 public:
  void AddPart(char operation, double value) {
    parts_.emplace_back(operation, value);
  }

  [[nodiscard]]
  double Apply(double value) const {
    for (auto part : parts_) {
      value = part.Apply(value);
    }
    return value;
  }

  void Invert() {
    for (FunctionPart& part : parts_) {
      part.Invert();
    }
    reverse(begin(parts_), end(parts_));
  }

 private:
  vector<FunctionPart> parts_;
};
