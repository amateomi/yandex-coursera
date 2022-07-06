/*
 * Дополните класс Person из задачи «Имена и фамилии — 2» конструктором,
 * позволяющим задать имя и фамилию человека при рождении, а также сам год
 * рождения. Класс не должен иметь конструктора по умолчанию.
 *
 * При получении на вход года, который меньше года рождения:
 * - методы GetFullName и GetFullNameWithHistory должны отдавать "No person";
 * - методы ChangeFirstName и ChangeLastName должны игнорировать запрос.
 *
 * Кроме того, необходимо объявить константными все методы, которые по сути ими
 * являются.
 */
#include <algorithm>
#include <iostream>
#include <deque>
#include <map>

using namespace std;

string NameByYear(const map<int, string>& names, int year) {
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

string NameHistoryByYear(const map<int, string>& names, int year) {
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
  for (const auto& name : name_history) {
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
  Person(const string& first_name,
         const string& last_name,
         int year) {
    first_names_[year] = first_name;
    last_names_[year] = last_name;
    birth_year_ = year;
  }

  void ChangeFirstName(int year, const string& first_name) {
    if (year >= birth_year_) {
      first_names_[year] = first_name;
    }
  }

  void ChangeLastName(int year, const string& last_name) {
    if (year >= birth_year_) {
      last_names_[year] = last_name;
    }
  }

  [[nodiscard]]
  string GetFullName(int year) const {
    if (year < birth_year_) {
      return "No person";
    }
    return MakeFullName(
        NameByYear(first_names_, year),
        NameByYear(last_names_, year)
    );
  }

  [[nodiscard]]
  string GetFullNameWithHistory(int year) const {
    if (year < birth_year_) {
      return "No person";
    }
    return MakeFullName(
        NameHistoryByYear(first_names_, year),
        NameHistoryByYear(last_names_, year)
    );
  }

 private:
  static string MakeFullName(const string& first_name_data,
                             const string& last_name_data) {
    if (first_name_data.empty() && last_name_data.empty()) {
      return "Incognito";
    } else if (first_name_data.empty()) {
      return last_name_data + " with unknown first name";
    } else if (last_name_data.empty()) {
      return first_name_data + " with unknown last name";
    } else {
      return first_name_data + ' ' + last_name_data;
    }
  }

  map<int, string> first_names_;
  map<int, string> last_names_;
  int birth_year_;
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
}
