/*
 * Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом
 * GetFullNameWithHistory.
 *
 * В отличие от метода GetFullName, метод GetFullNameWithHistory должен вернуть
 * не только последние имя и фамилию к концу данного года, но ещё и все
 * предыдущие имена и фамилии в обратном хронологическом порядке. Если текущие
 * факты говорят о том, что человек два раза подряд изменил фамилию или имя на
 * одно и то же, второе изменение при формировании истории нужно игнорировать.
 */
#include <algorithm>
#include <iostream>
#include <deque>
#include <map>

using namespace std;

string NameByYear(const map<int, string> &names, int year) {
  string name;
  for (auto[key, value] : names) {
    if (key <= year) {
      name = value;
    } else {
      break;
    }
  }
  return name;
}

string NameHistoryByYear(const map<int, string> &names, int year) {
  deque<string> name_history;
  for (auto[key, value] : names) {
    if (key <= year) {
      name_history.push_front(value);
    } else {
      break;
    }
  }

  auto new_end = unique(begin(name_history), end(name_history));
  name_history.erase(new_end, end(name_history));

  string result;
  int i = 0;
  for (const auto &name : name_history) {
    if (i == 0) {
      result = name;
    } else if (i == 1) {
      result += " (" + name;
    } else {
      result += ", " + name;
    }
    ++i;
  }
  if (i > 1) {
    result += ")";
  }
  return result;
}

class Person {
 public:
  void ChangeFirstName(int year, const string &first_name) {
    first_names_[year] = first_name;
  }

  void ChangeLastName(int year, const string &last_name) {
    last_names_[year] = last_name;
  }

  string GetFullName(int year) {
    const string kFirstName = NameByYear(first_names_, year);
    const string kLastName = NameByYear(last_names_, year);

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

  string GetFullNameWithHistory(int year) {
    const string kFirstNameHistory = NameHistoryByYear(first_names_, year);
    const string kLastNameHistory = NameHistoryByYear(last_names_, year);

    if (kFirstNameHistory.empty() && kLastNameHistory.empty()) {
      return "Incognito";
    } else if (kFirstNameHistory.empty()) {
      return kLastNameHistory + " with unknown first name";
    } else if (kLastNameHistory.empty()) {
      return kFirstNameHistory + " with unknown last name";
    } else {
      return kFirstNameHistory + ' ' + kLastNameHistory;
    }
  }

 private:
  map<int, string> first_names_;
  map<int, string> last_names_;
};

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1965, "Appolinaria");

  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeLastName(1965, "Volkova");
  person.ChangeLastName(1965, "Volkova-Sergeeva");

  for (int year : {1964, 1965, 1966}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
}