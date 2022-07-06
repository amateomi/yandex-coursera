/*
 * Определите структуру «Студент» со следующими полями: имя, фамилия, день,
 * месяц и год рождения. Создайте вектор из таких структур, заполните его из
 * входных данных и затем по запросам выведите нужные поля. Чтение и запись
 * данных в этой задаче производится с использованием стандартных потоков.
 *
 * Формат ввода
 * Первая строка содержит одно целое число N от 0 до 10000 — число студентов.
 * Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15
 * символов — имя и фамилию очередного студента, и три целых числа от 0 до
 * 1000000000 — день, месяц и год рождения.
 * Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.
 * Следующие M строк содержат строку длиной от 1 до 15 символов — запрос, и
 * целое число от 1 до 1000000000 — номер студента (нумерация начинается с 1).
 *
 * Формат вывода
 * Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию
 * K-го студента.
 * Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и
 * год рождения K-го студента.
 * Для остальных запросов выведите bad request.
 *
 * NB: неверные запросы могут выходить за границы, указанные для данных.
 */
#include <iostream>
#include <vector>

using namespace std;

struct Student {
  string first_name;
  string last_name;
  int birth_day;
  int birth_month;
  int birth_year;
};

int main() {
  int n;
  cin >> n;

  vector<Student> students(n);
  for (auto& student : students) {
    cin >> student.first_name
        >> student.last_name
        >> student.birth_day
        >> student.birth_month
        >> student.birth_year;
  }

  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    string command;
    cin >> command;
    int id;
    cin >> id;
    --id;

    if (!(0 <= id && id < n)) {
      cout << "bad request" << endl;
      continue;
    }

    if (command == "name") {
      cout << students[id].first_name << ' '
           << students[id].last_name << endl;
    } else if (command == "date") {
      cout << students[id].birth_day << '.'
           << students[id].birth_month << '.'
           << students[id].birth_year << endl;
    } else {
      cout << "bad request" << endl;
    }
  }
}
