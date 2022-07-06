/*
 * Реализуйте рассказанный на лекции класс Function, позволяющий создавать,
 * вычислять и инвертировать функцию, состоящую из следующих элементарных
 * операций:
 * - прибавить вещественное число x;
 * - вычесть вещественное число x.
 *
 * При этом необходимо объявить константными все методы, которые по сути такими
 * являются.
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
    if (operation_ == '+') {
      return source_value + value_;
    } else if (operation_ == '-') {
      return source_value - value_;
    } else {
      return {};
    }
  }

  void Invert() {
    if (operation_ == '+') {
      operation_ = '-';
    } else {  // operation == '-'
      operation_ = '+';
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
