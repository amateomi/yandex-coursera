/*
 * У каждого спортсмена на футболке написан уникальный номер. Спортсмены по
 * очереди выходят из раздевалки и должны построиться на стадионе. Тренер
 * каждому выходящему спортсмену называет номер того спортсмена, перед которым
 * нужно встать. Если спортсмена с названным номером на поле нет, то нужно
 * встать в конец шеренги.
 *
 * В стандартном вводе сначала задано натуральное число n, не превосходящее
 * 100000, — количество спортсменов. Далее идут n пар неотрицательных целых
 * чисел, не превосходящих 100000. Первое число в паре — номер очередного
 * выходящего спортсмена. Второе число в паре — номер того спортсмена, перед
 * которым должен встать текущий.
 *
 * Напечатайте в стандартный вывод номера спортсменов в порядке построения на
 * поле.
 *
 * Ограничение по времени — 0,8 с.
 */
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  list<int>                   athletes;
  vector<list<int>::iterator> arrived_athletes(100'000 + 1,
                                               athletes.end());

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int new_athlete, before_athlete;
    cin >> new_athlete >> before_athlete;
    auto& it = arrived_athletes[before_athlete];
    if (it != athletes.end()) {
      arrived_athletes[new_athlete] = athletes.insert(it, new_athlete);
    } else {
      athletes.push_back(new_athlete);
      arrived_athletes[new_athlete] = prev(athletes.end());
    }
  }

  for (const auto& athlete : athletes) {
    cout << athlete << endl;
  }
}
