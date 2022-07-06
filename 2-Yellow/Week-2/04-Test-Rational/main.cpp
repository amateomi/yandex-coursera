/*
 * Класс Rational представляет собой рациональное число и имеет следующий
 * интерфейс:
 *
 * class Rational {
 *  public:
 *   Rational();
 *   Rational(int numerator, int denominator);
 *
 *   int Numerator() const;
 *   int Denominator() const;
 * };
 *
 * Список требований, предъявляемых к реализации интерфейса класса Rational:
 * 1. Конструктор по умолчанию должен создавать дробь с числителем 0 и
 *    знаменателем 1.
 * 2. При конструировании объекта класса Rational с параметрами p и q должно
 *    выполняться сокращение дроби p/q.
 * 3. Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь
 *    отрицательный числитель и положительный знаменатель.
 * 4. Если дробь p/q положительная, то объект Rational(p, q) должен иметь
 *    положительные числитель и знаменатель (обратите внимание на случай
 *    Rational(-2, -3)).
 * 5. Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
 *
 * Разработайте набор юнит-тестов, которые будут проверять корректность
 * реализации класса Rational. Тестировать случай, когда знаменатель равен нулю,
 * не надо.
 */
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>
#include <random>

using namespace std;

template<class T>
ostream& operator<<(ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template<class T>
ostream& operator<<(ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template<class K, class V>
ostream& operator<<(ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
 public:
  template<class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count_;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count_;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count_ > 0) {
      cerr << fail_count_ << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

 private:
  int fail_count_ = 0;
};

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

    // true - positive, false - negative
    auto result_sign = [numerator, denominator]() {
      return numerator > 0 && denominator > 0
          || numerator < 0 && denominator < 0;
    };

    numerator_ = result_sign() ? abs(numerator)
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

void TestDefaultConstructor() {
  Rational rational;
  Assert(rational.Numerator() == 0 && rational.Denominator() == 1,
         "default constructor");
}

void TestReduction() {
  random_device device;
  mt19937 generator(device());
  uniform_int_distribution<int> distribution(1, numeric_limits<int>::max());
  for (int i = 0; i < 100; ++i) {
    const int kNumerator = distribution(generator);
    const int kDenominator = distribution(generator);

    const int kGcd = gcd(kNumerator, kDenominator);

    const Rational kR1(kNumerator, kDenominator);
    const Rational kR2(kNumerator / kGcd, kDenominator / kGcd);

    AssertEqual(vector{kR1.Numerator(), kR1.Denominator()},
                vector{kR2.Numerator(), kR2.Denominator()});
  }
}

void TestSign() {
  {
    Rational rational(2, 3);
    Assert(rational.Numerator() > 0 && rational.Denominator() > 0,
           "numerator positive, denominator positive");
  }
  {
    Rational rational(-2, 3);
    Assert(rational.Numerator() < 0 && rational.Denominator() > 0,
           "numerator negative, denominator positive");
  }
  {
    Rational rational(2, -3);
    Assert(rational.Numerator() < 0 && rational.Denominator() > 0,
           "numerator positive, denominator negative");
  }
  {
    Rational rational(-2, -3);
    Assert(rational.Numerator() > 0 && rational.Denominator() > 0,
           "numerator negative, denominator negative");
  }
}

void TestZeroNumerator() {
  {
    Rational rational(0, 10);
    Assert(rational.Numerator() == 0 && rational.Denominator() == 1,
           "0/10");
  }
  {
    Rational rational(-0, 10);
    Assert(rational.Numerator() == 0 && rational.Denominator() == 1,
           "-0/10");
  }
  {
    Rational rational(0, -10);
    Assert(rational.Numerator() == 0 && rational.Denominator() == 1,
           "0/-10");
  }
  {
    Rational rational(0, 1);
    Assert(rational.Numerator() == 0 && rational.Denominator() == 1,
           "-0/-10");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
  runner.RunTest(TestReduction, "TestReduction");
  runner.RunTest(TestSign, "TestSign");
  runner.RunTest(TestZeroNumerator, "TestZeroNumerator");
}

