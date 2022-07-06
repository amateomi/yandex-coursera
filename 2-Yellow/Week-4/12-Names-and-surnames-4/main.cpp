/*
 * Решите задачу «Имена и фамилии — 1» более эффективно, использовав двоичный
 * поиск в методе Person::GetFullName.
 */
#include <iostream>
#include <map>

using namespace std;

class Person {
 public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names_[year] = first_name;
  }

  void ChangeLastName(int year, const string& last_name) {
    last_names_[year] = last_name;
  }

  string GetFullName(int year) {
    auto name_by_year = [year](const map<int, string>& m) -> string {
      auto it = m.upper_bound(year);
      if (it == m.begin()) {
        return "";
      }
      return prev(it)->second;
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

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
}