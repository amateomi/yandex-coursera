/*
 * Итак, теперь у нас с вами есть полноценный тип для представления обыкновенных
 * дробей: класс Rational интегрирован в язык с помощью перегрузки операторов и
 * не позволяет выполнять некорректные операции за счёт выбрасывания исключений.
 * Давайте на основе класса Rational создадим простой калькулятор для
 * обыкновенных дробей.
 *
 * Вам надо написать программу, которая считывает из стандартного ввода одну
 * строку в формате ДРОБЬ_1 операция ДРОБЬ_2.  ДРОБЬ_1 и ДРОБЬ_2 имеют формат
 * X/Y, где X — целое, а Y — целое неотрицательное число. Операция — это один из
 * символов '+', '-', '*', '/'.
 *
 * Если ДРОБЬ_1 или ДРОБЬ_2 является некорректной обыкновенной дробью, ваша
 * программа должна вывести в стандартный вывод сообщение "Invalid argument".
 * Если считанная операция — это деление на ноль, выведите в стандартный вывод
 * сообщение "Division by zero". В противном случае выведите результат операции.
 */
#include <iostream>
#include <numeric>

using namespace std;

class Rational {
 public:
  Rational() {
    numerator_ = 0;
    denominator_ = 1;
  }

  Rational(int numerator, int denominator) {
    if (denominator == 0) {
      throw invalid_argument("Invalid argument");
    }

    const auto kGcd = gcd(numerator, denominator);
    numerator /= kGcd;
    denominator /= kGcd;

    numerator_ = (static_cast<long long>(numerator) * static_cast<long long>(denominator) > 0)
                 ? abs(numerator)
                 : -abs(numerator);
    denominator_ = abs(denominator);
  }

  [[nodiscard]]
  int Numerator() const {
    return numerator_;
  }

  [[nodiscard]]
  int Denominator() const {
    return denominator_;
  }

 private:
  int numerator_;
  int denominator_;
};

bool operator==(const Rational& lhs, const Rational& rhs) {
  return lhs.Numerator() == rhs.Numerator()
      && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
  return {lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
  return {lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
  return {lhs.Numerator() * rhs.Numerator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
  if (rhs.Numerator() == 0) {
    throw domain_error("Division by zero");
  }
  return {lhs.Numerator() * rhs.Denominator(),
          lhs.Denominator() * rhs.Numerator()};
}

istream& operator>>(istream& input, Rational& rational) {
  char separator;
  int numerator, denominator;
  input >> numerator >> separator >> denominator;
  if (input && separator == '/') {
    rational = {numerator, denominator};
  }
  return input;
}

ostream& operator<<(ostream& output, const Rational& rational) {
  output << rational.Numerator() << '/' << rational.Denominator();
  return output;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
  return lhs.Numerator() * rhs.Denominator()
      < rhs.Numerator() * lhs.Denominator();
}

int main() {
  try {
    char operation;
    Rational x, y;
    cin >> x >> operation >> y;

    Rational result;
    switch (operation) {
      case '+':result = x + y;
        break;
      case '-':result = x - y;
        break;
      case '*':result = x * y;
        break;
      case '/':result = x / y;
        break;
      default:break;
    }
    cout << result << endl;

  } catch (exception& err) {
    cout << err.what() << endl;
  }
}
