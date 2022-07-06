/*
 * Вспомним класс Rational, который мы реализовали в задачах, посвящённых
 * перегрузке операторов. Там специально говорилось, что в тестах объекты класса
 * Rational никогда не создаются с нулевым знаменателем и никогда не выполняется
 * деление на ноль. Настало время избавиться от этого ограничения и научиться
 * обрабатывать нулевой знаменатель и деление на ноль. В этой задаче вам
 * предстоит это сделать.
 *
 * Поменяйте реализацию конструктора класса Rational так, чтобы он выбрасывал
 * исключение invalid_argument, если знаменатель равен нулю. Кроме того,
 * переделайте реализацию оператора деления для класса Rational так, чтобы он
 * выбрасывал исключение domain_error, если делитель равен нулю.
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
      throw invalid_argument("division by zero");
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
    throw domain_error("division by zero");
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
    Rational r(1, 0);
    cout << "Doesn't throw in case of zero denominator" << endl;
    return 1;
  } catch (invalid_argument&) {
  }

  try {
    auto x = Rational(1, 2) / Rational(0, 1);
    cout << "Doesn't throw in case of division by zero" << endl;
    return 2;
  } catch (domain_error&) {
  }

  cout << "OK" << endl;
}
