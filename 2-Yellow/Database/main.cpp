/*
 * В курсе «Белый пояс по С++» финальным заданием была разработка базы данных,
 * которая работала с парами (дата, событие). В этой задаче вам нужно развить
 * эту базу данных, научив её выбирать и удалять события, удовлетворяющие
 * заданному условию, а также разделив её код на несколько файлов.
 *
 * Более подробно, ваша программа должна уметь обрабатывать набор команд:
 * - Add dateevent — добавить в базу данных пару (date, event);
 * - Print — вывести всё содержимое базы данных;
 * - Find condition — вывести все записи, содержащиеся в базе данных, которые
 *   удовлетворяют условию condition;
 * - Del condition — удалить из базы все записи, которые удовлетворяют условию
 *   condition;
 * - Last date — вывести запись с последним событием, случившимся не позже
 *   данной даты.
 *
 * Условия в командах Find и Del накладывают определённые ограничения на даты и
 * события, например:
 * - Find date < 2017-11-06 — найти все события, которые случились раньше
 *   6 ноября 2017 года;
 * - Del event != "holiday" — удалить из базы все события, кроме «holiday»;
 * - Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event" —
 *   найти всё события «sport event», случившиеся в первой половине 2017 года;
 * - Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event") —
 *   удалить из базы все события «holiday» и «sport event», случившиеся до 2017
 *   года.
 *
 * В командах обоих типов условия могут быть пустыми: под такое условие попадают
 * все события.
 */

#include "database.h"
#include "condition_parser.h"
#include "test_runner.h"

#include <iostream>

using namespace std;

string ParseEvent(istream& is) {
  is >> ws;
  string s;
  getline(is, s);
  return s;
}

void TestAll();

int main() {
  TestAll();

  Database db;

  for (string line; getline(cin, line);) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
        cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
        cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}
