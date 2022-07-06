/*
 * В первом курсе «Белый пояс по С++» у нас была задача «Имена и фамилии — 1».
 * В ней надо было разработать класс Person, поддерживающий историю изменений
 * человеком своих фамилии и имени. В данной задаче вам надо разработать
 * юнит-тесты на реализацию класса Person. При разработке тестов учитывайте
 * ограничения, которые накладывает на класс Person условие задачи «Имена и
 * фамилии — 1».
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

class Person {
 public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names_[year] = first_name;
  }

  void ChangeLastName(int year, const string& last_name) {
    last_names_[year] = last_name;
  }

  string GetFullName(int year) {
    auto name_by_year = [year](const map<int, string>& m) {
      string name;
      for (auto[key, value] : m) {
        if (key <= year) {
          name = value;
        } else {
          break;
        }
      }
      return name;
    };

    const string kFirstName = name_by_year(first_names_);
    const string kLastName = name_by_year(last_names_);

    if (kFirstName.empty() && kLastName.empty()) {
      return "Incognito";
    } else if (kFirstName.empty()) {
      return kLastName + " with unknown first name";
    } else if (kLastName.empty()) {
      return kFirstName + " with unknown last name";
    } else {
      return kFirstName + ' ' + kLastName;
    }
  }

 private:
  map<int, string> first_names_;
  map<int, string> last_names_;
};

void TestIncognito() {
  Person p;
  AssertEqual(p.GetFullName(1900), "Incognito", "empty person");
  p.ChangeFirstName(2000, "Petr");
  p.ChangeLastName(2020, "Ivanovich");
  AssertEqual(p.GetFullName(1900), "Incognito",
              "after adding records in future");
}

void TestUnknownFirstName() {
  auto add_unknown_first_name = [](const string& last_name) {
    return last_name + " with unknown first name";
  };

  Person p;
  {
    string white = "White";
    p.ChangeLastName(1900, white);
    AssertEqual(p.GetFullName(1900), add_unknown_first_name(white),
                "year of record");
    AssertEqual(p.GetFullName(1915), add_unknown_first_name(white),
                "after year of record");
  }
  {
    string anderson = "Anderson";
    p.ChangeLastName(1920, anderson);
    AssertEqual(p.GetFullName(1920), add_unknown_first_name(anderson),
                "year of new last name record");
    AssertEqual(p.GetFullName(1925), add_unknown_first_name(anderson),
                "after year of new last name record");
  }
}

void TestUnknownLastName() {
  auto add_unknown_last_name = [](const string& first_name) {
    return first_name + " with unknown last name";
  };

  Person p;
  {
    string andrey = "Andrey";
    p.ChangeFirstName(1900, andrey);
    AssertEqual(p.GetFullName(1900), add_unknown_last_name(andrey),
                "year of record");
    AssertEqual(p.GetFullName(1915), add_unknown_last_name(andrey),
                "after year of record");
  }
  {
    string alex = "Alex";
    p.ChangeFirstName(1920, alex);
    AssertEqual(p.GetFullName(1920), add_unknown_last_name(alex),
                "year of new first name record");
    AssertEqual(p.GetFullName(1925), add_unknown_last_name(alex),
                "after year of new first name record");
  }
}

void TestFullName() {
  auto full_name = [](const string& first_name, const string& last_name) {
    return first_name + ' ' + last_name;
  };

  Person p;

  // first full name record
  string andrey = "Andrey";
  p.ChangeFirstName(1910, andrey);
  string anderson = "Anderson";
  p.ChangeLastName(1910, anderson);

  // last full name record
  string alex = "Alex";
  p.ChangeFirstName(1940, alex);
  string white = "White";
  p.ChangeLastName(1940, white);

  // add new name in middle
  string ivan = "Ivan";
  p.ChangeFirstName(1920, ivan);

  // add new last name in middle
  string ivanov = "Ivanov";
  p.ChangeLastName(1930, ivanov);

  AssertEqual(p.GetFullName(1910), full_name(andrey, anderson),
              "year of first full name record");
  AssertEqual(p.GetFullName(1915), full_name(andrey, anderson),
              "after year of first full name record");

  AssertEqual(p.GetFullName(1920), full_name(ivan, anderson),
              "year of new first name record");
  AssertEqual(p.GetFullName(1925), full_name(ivan, anderson),
              "after year of new first name record");

  AssertEqual(p.GetFullName(1930), full_name(ivan, ivanov),
              "year of new last name record");
  AssertEqual(p.GetFullName(1935), full_name(ivan, ivanov),
              "after year of new last name record");

  AssertEqual(p.GetFullName(1940), full_name(alex, white),
              "year of last full name record");
  AssertEqual(p.GetFullName(1945), full_name(alex, white),
              "after year of last full name record");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIncognito, "TestIncognito");
  runner.RunTest(TestUnknownFirstName, "TestUnknownFirstName");
  runner.RunTest(TestUnknownLastName, "TestUnknownLastName");
  runner.RunTest(TestFullName, "TestFullName");
}
