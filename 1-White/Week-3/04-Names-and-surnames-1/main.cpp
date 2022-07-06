/*
 * Реализуйте класс для человека, поддерживающий историю изменений человеком
 * своих фамилии и имени.
 *
 * Считайте, что в каждый год может произойти не более одного изменения фамилии
 * и не более одного изменения имени. При этом с течением времени могут
 * открываться всё новые факты из прошлого человека, поэтому года́ в
 * последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны
 * возрастать.
 *
 * Гарантируется, что все имена и фамилии непустые.
 *
 * Строка, возвращаемая методом GetFullName, должна содержать разделённые одним
 * пробелом имя и фамилию человека по состоянию на конец данного года.
 * - Если к данному году не случилось ни одного изменения фамилии и имени,
 *   верните строку "Incognito".
 * - Если к данному году случилось изменение фамилии, но не было ни одного
 *   изменения имени, верните "last_name with unknown first first_name".
 * - Если к данному году случилось изменение имени, но не было ни одного
 *   изменения фамилии, верните "first_name with unknown last first_name".
 */
#include <iostream>
#include <map>

using namespace std;

class Person {
 public:
  void ChangeFirstName(int year, const string &first_name) {
    first_names_[year] = first_name;
  }

  void ChangeLastName(int year, const string &last_name) {
    last_names_[year] = last_name;
  }

  string GetFullName(int year) {
    auto name_by_year = [year](const map<int, string> &m) {
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