/*
* Часть 1
*
* В первой части Вам надо реализовать класс Rational, который представляет
* собой рациональное число вида p/q, где p — целое, а q — натуральное и
* диапазоны возможных значений p, q таковы, что могут быть представлены типом
* int.
*
* Класс Rational должен гарантировать, что p/q — это несократимая дробь.
*
* Список требований, предъявляемых к реализации интерфейса класса Rational:
* - Конструктор по умолчанию должен создавать дробь с числителем 0 и
*   знаменателем 1.
* - При конструировании объекта класса Rational с параметрами p и q должно
*   выполняться сокращение дроби p/q (здесь вам может пригодиться решение
*   задачи «Наибольший общий делитель»).
* - Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь
*   отрицательный числитель и положительный знаменатель.
* - Если дробь p/q положительная, то объект Rational(p, q) должен иметь
*   положительные числитель и знаменатель (обратите внимание на случай
*   Rational(-2, -3)).
* - Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
*
* Гарантируется, что ни в одном из тестов, на которых будет тестироваться ваша
* реализация, не будет знаменателя, равного нулю.
*
* Часть 2
*
* Реализуйте для класса Rational операторы ==, + и - так, чтобы операции с
* дробями можно было записывать естественным образом.
*
* Гарантируется, что во всех тестах, на которых будет тестироваться ваша
* реализация, числители и знаменатели ВСЕХ дробей (как исходных, так и
* получившихся в результате соответствующих арифметических операций) будут
* укладываться в диапазон типа int.
*
* Часть 3
*
* Аналогично предыдущей части, реализуйте операторы * и /.
*
* Как и в предыдущем случае, гарантируется, что во всех тестах, на которых
* будет тестироваться ваша реализация, числители и знаменатели ВСЕХ дробей
* (как исходных, так и получившихся в результате соответствующих арифметических
* операций) будут укладываться в диапазон типа int.
*
* Кроме того, гарантируется, что ни в одном из тестов, на которых будет
* тестироваться ваша реализация, не будет выполняться деление на ноль.
*
* Часть 4
*
* В этой части вам нужно реализовать операторы ввода и вывода для класса
* Rational.
*
* Часть 5
*
* Наконец, вам нужно реализовать возможность использовать объекты класса
* Rational в качестве элементов контейнера set и ключей в контейнере map.
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
