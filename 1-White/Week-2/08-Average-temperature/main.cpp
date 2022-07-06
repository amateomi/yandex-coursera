/*
 * Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
 * Найдите номера дней (в нумерации с нуля) со значением температуры выше
 * среднего арифметического за все N дней.
 * 
 * Гарантируется, что среднее арифметическое значений температуры является
 * целым числом.
 *
 * Формат ввода:
 * Вводится число N, затем N неотрицательных целых чисел —
 * значения температуры в 0-й, 1-й, ... (N−1)-й день.
 *
 * Формат вывода:
 * Первое число K — количество дней, значение температуры в которых выше
 * среднего арифметического. Затем K целых чисел — номера этих дней.
 */
#include <iostream>
#include <vector>

using namespace std;

size_t Avg(const vector<size_t>& days) {
  size_t avg = 0;
  for (auto t : days) {
    avg += t;
  }
  return avg / days.size();
}

vector<size_t> HigherThanAvg(const vector<size_t>& days, size_t avg) {
  vector<size_t> result;
  for (size_t i = 0; i < days.size(); ++i) {
    if (days[i] > avg) {
      result.push_back(i);
    }
  }
  return result;
}

int main() {
  int n;
  cin >> n;
  vector<size_t> days(n);
  for (auto& t : days) {
    cin >> t;
  }
  days = HigherThanAvg(days, Avg(days));
  cout << days.size() << endl;
  for (auto t : days) {
    cout << t << ' ';
  }
}
