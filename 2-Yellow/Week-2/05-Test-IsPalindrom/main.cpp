/*
 * В этой задаче вам нужно разработать набор юнит-тестов для функции:
 *
 * bool IsPalindrom(const string& s);
 *
 * Эта функция проверяет, является ли строка s палиндромом. Палиндром — это
 * слово или фраза, которые одинаково читаются слева направо и справа налево.
 * Примеры палиндромов: madam, level, wasitacaroracatisaw
 *
 * Разработайте набор юнит-тестов, который будет принимать правильные реализации
 * функции IsPalindrom и отвергать неправильные. При этом учитывайте, что
 * правильная реализация функции:
 * - считает пустую строку палиндромом;
 * - считает строку из одного символа палиндромом;
 * - осуществляет обычное сравнение символов на равенство, не игнорируя никакие
 *   символы, в том числе пробельные.
 *
 * При разработке тестов подумайте, какие ошибки можно допустить при реализации
 * функции IsPalindrom. Примеры ошибок:
 * - игнорируется первый или последний символ;
 * - сравнение соответствующих символов завершается не в середине строки, а раньше;
 * - игнорируются пробелы
 */
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

bool IsPalindrom(const string& str) {
  for (size_t i = 0; i < str.size() / 2; ++i) {
    if (str[i] != str[str.size() - 1 - i]) {
      return false;
    }
  }
  return true;
}

void TestIsPalindrom() {
  Assert(IsPalindrom(""), "empty string is palindrome");
  Assert(IsPalindrom("a"), "one symbolic string is palindrome");
  Assert(IsPalindrom("abba"), "even characters");
  Assert(IsPalindrom("abcba"), "odd characters");

  Assert(!IsPalindrom("a bba"), "spaces shouldn't be ignored");
  Assert(!IsPalindrom("cabba"), "first character shouldn't be ignored");
  Assert(!IsPalindrom("abbac"), "last character shouldn't be ignored");
  Assert(!IsPalindrom("Abba"), "capital letters aren't equal to lower letters");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
}

