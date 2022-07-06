/*
 * Функция GetDistinctRealRootCount() возвращает количество уникальных
 * действительных корней уравнения ax² + bx + c = 0. Разработайте набор
 * юнит-тестов для проверки корректности реализации этой функции. Случай,
 * когда все три коэффициента равны нулю, тестировать не надо.
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

int GetDistinctRealRootCount(double a, double b, double c) {
  if (a == 0) {
    return static_cast<int>(b != 0);
  } else {
    double d = b * b - 4 * a * c;
    if (d < 0) {
      return 0;
    } else if (d == 0) {
      return 1;
    } else { // d > 0
      return 2;
    }
  }
}

void TestGetDistinctRealRootCount() {
  {
    AssertEqual(GetDistinctRealRootCount(0, 0, 3), 0, "a = b = 0");
    AssertEqual(GetDistinctRealRootCount(3, 2, 6), 0, "D < 0");
  }
  {
    AssertEqual(GetDistinctRealRootCount(0, 3, 5), 1, "linear equation");
    AssertEqual(GetDistinctRealRootCount(1, 4, 4), 1, "D = 0");
  }
  {
    AssertEqual(GetDistinctRealRootCount(2, 3, -1), 2, "D > 0");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestGetDistinctRealRootCount, "Test");
}



