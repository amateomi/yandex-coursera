/*
 * В этой задаче вам необходимо вычислить различные демографические показатели
 * для группы людей. Человек представляется структурой Person.
 *
 * Вам необходимо написать функцию PrintStats, получающую вектор людей,
 * вычисляющую и выводящую медианный возраст для каждой из следующих групп
 * людей:
 * - все люди;
 * - все женщины;
 * - все мужчины;
 * - все занятые женщины;
 * - все безработные женщины;
 * - все занятые мужчины;
 * - все безработные мужчины.
 * Все 7 чисел нужно вывести в строгом соответствии с форматом.
 *
 * Принимая вектор по значению (а не по константной ссылке), вы получаете
 * возможность модифицировать его копию произвольным образом и тем самым проще
 * произвести вычисления.
 *
 * Для вычисления медианного возраста группы людей вы должны использовать
 * функцию ComputeMedianAge. Эту функцию не нужно реализовывать самостоятельно:
 * мы реализовали её за вас и автоматически добавим к каждому вашему решению.
 *
 * Функцию ComputeMedianAge можно вызвать и для пустого набора людей: её
 * результат в этом случае и нужно считать медианным возрастом пустого набора
 * людей.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;
  Gender gender;
  bool is_employed;
};

template<typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

struct StatsPartitionBorders {
  vector<Person>::iterator gender;
  vector<Person>::iterator female_employment;
  vector<Person>::iterator male_employment;
};

StatsPartitionBorders PartitionStats(vector<Person>& persons) {
  auto gender_predicate = [](const Person& p) {
    return p.gender == Gender::FEMALE;
  };
  auto employment_predicate = [](const Person& p) {
    return p.is_employed;
  };

  StatsPartitionBorders borders;

  borders.gender = partition(persons.begin(),
                             persons.end(),
                             gender_predicate);

  borders.female_employment = partition(persons.begin(),
                                        borders.gender,
                                        employment_predicate);

  borders.male_employment = partition(borders.gender,
                                      persons.end(),
                                      employment_predicate);

  return borders;
}

void PrintStats(vector<Person> persons) {
  StatsPartitionBorders borders = PartitionStats(persons);

  auto print_line = [](int age, const string& details = "") {
    cout << "Median age " << details << (details.empty() ? "" : " ") << "= " << age << endl;
  };

  print_line(ComputeMedianAge(persons.begin(), persons.end()));
  print_line(ComputeMedianAge(persons.begin(), borders.gender), "for females");
  print_line(ComputeMedianAge(borders.gender, persons.end()), "for males");
  print_line(ComputeMedianAge(persons.begin(), borders.female_employment),
             "for employed females");
  print_line(ComputeMedianAge(borders.female_employment, borders.gender),
             "for unemployed females");
  print_line(ComputeMedianAge(borders.gender, borders.male_employment),
             "for employed males");
  print_line(ComputeMedianAge(borders.male_employment, persons.end()),
             "for unemployed males");
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
}
