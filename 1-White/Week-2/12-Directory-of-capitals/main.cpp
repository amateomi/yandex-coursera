/*
 * Реализуйте справочник столиц стран.
 *
 * На вход программе поступают следующие запросы:
 * - CHANGE_CAPITAL country new_capital — изменение столицы страны country на
 *   new_capital, либо добавление такой страны с такой столицей, если раньше её
 *   не было.
 * - RENAME old_country_name new_country_name — переименование страны из
 *   old_country_name в new_country_name.
 * - ABOUT country — вывод столицы страны country.
 * - DUMP — вывод столиц всех стран.
 *
 * Формат ввода
 * В первой строке содержится количество запросов Q, в следующих Q строках —
 * описания запросов. Все названия стран и столиц состоят лишь из латинских
 * букв, цифр и символов подчёркивания.
 *
 * Формат вывода
 * Выведите результат обработки каждого запроса:
 *
 * В ответ на запрос CHANGE_CAPITAL country new_capital выведите
 * - Introduce new country country with capital new_capital, если страны country
 *   раньше не существовало;
 * - Country country hasn't changed its capital, если страна country до текущего
 *   момента имела столицу new_capital;
 * - Country country has changed its capital from old_capital to new_capital,
 *   если страна country до текущего момента имела столицу old_capital, название
 *   которой не совпадает с названием new_capital.
 *
 * В ответ на запрос RENAME old_country_name new_country_name выведите
 * - Incorrect rename, skip, если новое название страны совпадает со старым,
 *   страна old_country_name не существует или страна new_country_name уже
 *   существует;
 * - Country old_country_name with capital capital has been renamed to
 *   new_country_name, если запрос корректен и страна имеет столицу capital.
 *
 * В ответ на запрос ABOUT country выведите
 * - Country country doesn't exist, если страны с названием country не
 *   существует;
 * - Country country has capital capital, если страна country существует и имеет
 *   столицу capital.
 *
 * В ответ на запрос DUMP выведите
 * - There are no countries in the world, если пока не было добавлено ни одной
 *   страны;
 * - последовательность пар вида country/capital, описывающую столицы всех
 *   стран, если в мире уже есть хотя бы одна страна. При выводе
 *   последовательности пары указанного вида необходимо упорядочить по названию
 *   страны и разделять между собой пробелом.
 */
#include <iostream>
#include <map>

using namespace std;

// key - country
// value - capital
map<string, string> capitals;

void ChangeCapital();
void Rename();
void About();
void Dump();

int main() {
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    string command;
    cin >> command;
    if (command == "DUMP") {
      Dump();
    } else if (command == "ABOUT") {
      About();
    } else if (command == "CHANGE_CAPITAL") {
      ChangeCapital();
    } else if (command == "RENAME") {
      Rename();
    }
  }
}

void ChangeCapital() {
  string country, new_capital;
  cin >> country >> new_capital;
  if (capitals.count(country) == 0) {
    cout << "Introduce new country " << country << " with capital " << new_capital << endl;
    capitals[country] = new_capital;
  } else if (capitals[country] == new_capital) {
    cout << "Country " << country << " hasn't changed its capital" << endl;
  } else {
    cout << "Country " << country << " has changed its capital from " << capitals[country] << " to " << new_capital
         << endl;
    capitals[country] = new_capital;
  }
}

void Rename() {
  string old_country_name, new_country_name;
  cin >> old_country_name >> new_country_name;
  if (old_country_name == new_country_name ||
      capitals.count(old_country_name) == 0 ||
      capitals.count(new_country_name) == 1) {
    cout << "Incorrect rename, skip" << endl;
  } else {
    cout << "Country " << old_country_name << " with capital " << capitals[old_country_name] << " has been renamed to "
         << new_country_name << endl;
    auto node = capitals.extract(old_country_name);
    node.key() = new_country_name;
    capitals.insert(std::move(node));
  }
}

void About() {
  string country;
  cin >> country;
  if (capitals.count(country) == 0) {
    cout << "Country " << country << " doesn't exist" << endl;
  } else {
    cout << "Country " << country << " has capital " << capitals[country] << endl;
  }
}

void Dump() {
  if (capitals.empty()) {
    cout << "There are no countries in the world" << endl;
  }
  for (auto[key, value] : capitals) {
    cout << key << '/' << value << ' ';
  }
}
