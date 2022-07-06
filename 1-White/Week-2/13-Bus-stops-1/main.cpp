/*
 * Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать
 * следующие запросы:
 * - NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с
 *   названием bus и stop_count остановками с названиями stop1, stop2, ...
 * - BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих
 *   через остановку stop.
 * - STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком
 *   автобусов, на которые можно пересесть на каждой из остановок.
 * - ALL_BUSES — вывести список всех маршрутов с остановками.
 *
 * Формат ввода
 * В первой строке ввода содержится количество запросов Q, затем в Q строках
 * следуют описания запросов.
 * Гарантируется, что все названия маршрутов и остановок состоят лишь из
 * латинских букв, цифр и знаков подчёркивания.
 * Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что
 * маршрут bus отсутствует, количество остановок больше 0, а после числа
 * stop_count следует именно такое количество названий остановок, причём все
 * названия в каждом списке различны.
 *
 * Формат вывода
 * Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:
 * - На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов,
 *   проезжающих через эту остановку, в том порядке, в котором они создавались
 *   командами NEW_BUS. Если остановка stop не существует, выведите No stop.
 * - На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в
 *   отдельных строках в том порядке, в котором они были заданы в
 *   соответствующей команде NEW_BUS. Описание каждой остановки stop должно
 *   иметь вид Stop stop: bus1 bus2 ..., где bus1 bus2 ... — список автобусов,
 *   проезжающих через остановку stop, в порядке, в котором они создавались
 *   командами NEW_BUS, за исключением исходного маршрута bus. Если через
 *   остановку stop не проезжает ни один автобус, кроме bus, вместо списка
 *   автобусов для неё выведите no interchange. Если маршрут bus не существует,
 *   выведите No bus.
 * - На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке.
 *   Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ...,
 *   где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором
 *   они были заданы в соответствующей команде NEW_BUS. Если автобусы
 *   отсутствуют, выведите No bus_to_stops.
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// key - bus number
// value - bus stops names
map<string, vector<string>> bus_to_stops;
// Store order of entered buses
vector<string> buses;

void NewBus();
void BusesForStop();
void StopsForBus();
void AllBuses();

bool PrintBusesOnStop(const string& stop, const string& except_bus = "") {
  bool stop_exist = false;
  for (const auto& bus : buses) {
    if (bus == except_bus) {
      continue;
    }
    const auto& stops = bus_to_stops[bus];
    if (find(begin(stops), end(stops), stop) != end(stops)) {
      stop_exist = true;
      cout << bus << ' ';
    }
  }
  return stop_exist;
}

int main() {
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    string command;
    cin >> command;
    if (command == "NEW_BUS") {
      NewBus();
    } else if (command == "BUSES_FOR_STOP") {
      BusesForStop();
    } else if (command == "STOPS_FOR_BUS") {
      StopsForBus();
    } else if (command == "ALL_BUSES") {
      AllBuses();
    }
  }
}

void NewBus() {
  string bus;
  int stop_count;
  cin >> bus >> stop_count;
  vector<string> new_bus(stop_count);
  for (auto& stop : new_bus) {
    cin >> stop;
  }
  bus_to_stops[bus] = new_bus;
  buses.push_back(bus);
}

void BusesForStop() {
  string stop;
  cin >> stop;
  if (!PrintBusesOnStop(stop)) {
    cout << "No stop";
  }
  cout << endl;
}

void StopsForBus() {
  string bus;
  cin >> bus;
  if (bus_to_stops.count(bus) == 0) {
    cout << "No bus" << endl;
    return;
  }
  for (const auto& stop : bus_to_stops[bus]) {
    cout << "Stop " << stop << ": ";
    if (!PrintBusesOnStop(stop, bus)) {
      cout << "no interchange";
    }
    cout << endl;
  }
}

void AllBuses() {
  if (bus_to_stops.empty()) {
    cout << "No buses" << endl;
    return;
  }
  for (auto[bus, stops] : bus_to_stops) {
    cout << "Bus " << bus << ": ";
    for (const auto& s : stops) {
      cout << s << ' ';
    }
    cout << endl;
  }
}