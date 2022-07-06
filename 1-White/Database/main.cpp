/*
 * Необходимо написать программу на С++, которая реализует работу с простой
 * базой данных (сокращённо «БД»). Программа будет общаться с пользователем
 * через стандартный ввод и вывод (потоки stdin и stdout).
 * Будем хранить в нашей БД пары вида: дата, событие. Определим дату как строку
 * вида Год-Месяц-День, где Год, Месяц и День — целые числа.
 * Событие определим как строку из произвольных печатных символов без
 * разделителей внутри (пробелов, табуляций и пр.). Событие не может быть пустой
 * строкой. В одну и ту же дату может произойти много разных событий, БД должна
 * суметь их все сохранить. Одинаковые события, произошедшие в один и тот же
 * день, сохранять не нужно: достаточно сохранить только одно из них.
 *
 * Наша БД должна понимать определённые команды, чтобы с ней можно было
 * взаимодействовать:
 *
 * - добавление события:                        Add Дата Событие
 * - удаление события:                          Del Дата Событие
 * - удаление всех событий за конкретную дату:  Del Дата
 * - поиск событий за конкретную дату:          Find Дата
 * - печать всех событий за все даты:           Print
 *
 * Все команды, даты и события при вводе разделены пробелами. Команды
 * считываются из стандартного ввода. В одной строке может быть ровно одна
 * команда, но можно ввести несколько команд в несколько строк. На вход также
 * могут поступать пустые строки — их следует игнорировать и продолжать
 * обработку новых команд в последующих строках.
 *
 *
 * Добавление события (Add Дата Событие)
 * При добавлении события БД должна его запомнить и затем показывать его при
 * поиске (командой Find) или печати (командой Print). Если указанное событие
 * для данной даты уже существует, повторное его добавление нужно игнорировать.
 * В случае корректного ввода (см. раздел «Обработка ошибок ввода») программа
 * ничего не должна выводить на экран.
 *
 * Удаление события (Del Дата Событие)
 * Команда должна удалить добавленное ранее событие с указанным именем в
 * указанную дату, если оно существует. Если событие найдено и удалено,
 * программа должна вывести строку «Deleted successfully» (без кавычек). Если
 * событие в указанную дату не найдено, программа должна вывести строку «Event
 * not found» (без кавычек).
 *
 * Удаление нескольких событий (Del Дата)
 * Команда удаляет все ранее добавленные события за указанную дату. Программа
 * всегда должна выводить строку вида «Deleted N events», где N — это количество
 * всех найденных и удалённых событий. N может быть равно нулю, если в указанную
 * дату не было ни одного события.
 *
 * Поиск событий (Find Дата)
 * Найти и распечатать ранее добавленные события в указанную дату. Программа
 * должна вывести на печать только сами события, по одному на строке. События
 * должны быть отсортированы по возрастанию в порядке сравнения строк между
 * собой (тип string).
 *
 * Печать всех событий (Print)
 * С помощью этой команды можно показать полное содержимое нашей БД. Программа
 * должна вывести на печать все пары Дата Событие по одной на строке. Все пары
 * должны быть отсортированы по дате, а события в рамках одной даты должны быть
 * отсортированы по возрастанию в порядке сравнения строк между собой (тип
 * string). Даты должны быть отформатированы специальным образом: ГГГГ-ММ-ДД,
 * где Г, М, Д — это цифры чисел года, месяца и дня соответственно. Если
 * какое-то число имеет меньше разрядов, то оно должно дополняться нулями,
 * например, 0001-01-01 — первое января первого года. Вам не понадобится
 * выводить дату с отрицательным значением года.
 *
 * Обработка ошибок ввода
 * Ввод в этой задаче не всегда корректен: некоторые ошибки ввода ваша программа
 * должна корректно обрабатывать.
 *
 * Какие ошибки ввода нужно обрабатывать:
 * Если пользователь ввёл неизвестную команду, то программа должна об этом
 * сообщить, выведя строку «Unknown command: COMMAND», где COMMAND — это та
 * команда, которую ввёл пользователь. Командой считается первое слово в строке
 * (до пробела).
 * Если дата не соответствует формату Год-Месяц-День, где Год, Месяц и День —
 * произвольные целые числа, то программа должна напечатать «Wrong date format:
 * DATE», где DATE — это то, что пользователь ввёл вместо даты (до пробела).
 * Обратите внимание, что части даты разделяются ровно одним дефисом, а сама
 * дата не должна содержать лишних символов ни перед годом, ни после дня. Части
 * даты не могут быть пустыми, но могут быть нулевыми и даже отрицательными.
 * Если формат даты верен, необходимо проверить валидность месяца и дня.
 * - Если номер месяца не является числом от 1 до 12, выведите «Month value is
 *   invalid: MONTH», где MONTH — это неверный номер месяца, например, 13 или -1
 * - Если месяц корректен, а день не лежит в диапазоне от 1 до 31, выведите «Day
 *   value is invalid: DAY», где DAY — это неверный номер дня в месяце, например,
 *   39 или 0.
 * Обратите внимание, что:
 * - Значение года проверять отдельно не нужно.
 * - Не нужно проверять календарную корректность даты: количество дней в каждом
 *   месяце считается равным 31, високосные года учитывать не нужно.
 * - Если неверны как месяц, так и день, то нужно вывести одно сообщение об
 *   ошибке в месяце.
 * Примеры:
 * - 1-1-1 — корректная дата;
 * - -1-1-1 — корректная дата (год -1, месяц 1, день 1);
 * - 1--1-1 — дата в верном формате, но с некорректным месяцем -1;
 * - 1---1-1 — дата в неверном формате: месяц не может начинаться с двух дефисов
 * - 1-+1-+1 — корректная дата, так как +1 это целое число
 * После обработки любой из описанных ошибок ввода и печати сообщения программа
 * должна завершать своё выполнение.
 *
 * Какие ошибки ввода не нужно обрабатывать:
 * Мы не ставим своей целью сломать вашу программу всеми возможными способами
 * поэтому за исключением описанного в предыдущем пункте, вы можете полагаться
 * на корректность ввода. В частности, мы гарантируем, что:
 * - Каждая команда занимает целиком ровно одну строку, хотя во вводе могут быть
 *   и пустые строки (их нужно игнорировать).
 * - События всегда содержат указанное количество аргументов: после команды Add
 *   всегда следуют дата и событие, после команды Find всегда следует дата,
 *   после команды Del всегда следует дата и, возможно, событие, а команда Print
 *   не содержит дополнительной информации.
 * - Все команды, даты и события являются непустыми строками и не содержат
 *   пробелов и прочих пробельных символов. (В частности, наши тесты не содержат
 *   команды «Add 2018-02-12», потому что в ней после даты отсутствует название
 *   события.) С другой стороны, команда Del может не содержать события после
 *   даты: в этом случае нужно удалить все события за указанную дату (см. раздел
 *   «Удаление нескольких событий»).
 * - Несмотря на то, что дата с отрицательным значением года считается
 *   корректной, тесты устроены так, что её не понадобится выводить в команде
 *   Print.
 */
#include <iostream>
#include <iomanip>
#include <map>
#include <set>

using namespace std;

struct Year {
  int value;
  explicit Year(int year) { value = year; }
};
struct Month {
  int value;
  explicit Month(int month) { value = month; }
};
struct Day {
  int value;
  explicit Day(int day) { value = day; }
};

class Date {
 public:
  Date() = default;
  Date(Year year, Month month, Day day) {
    if (month.value < 1 || 12 < month.value) {
      throw invalid_argument("Month value is invalid: "
                                 + to_string(month.value));
    }
    if (day.value < 1 || 31 < day.value) {
      throw invalid_argument("Day value is invalid: "
                                 + to_string(day.value));
    }
    year_ = year.value;
    month_ = month.value;
    day_ = day.value;
  }

  [[nodiscard]]
  int GetYear() const {
    return year_;
  }
  [[nodiscard]]
  int GetMonth() const {
    return month_;
  }
  [[nodiscard]]
  int GetDay() const {
    return day_;
  }

 private:
  int year_ = 0;
  int month_ = 1;
  int day_ = 1;
};

istream& operator>>(istream& in, Date& date) {
  string date_str;
  in >> date_str;

  auto ensure_and_skip_delimiter = [date_str](istream& in) {
    // Throw exception when less than 2 characters and next is not '-'
    if (in.rdbuf()->in_avail() < 2 || in.peek() != '-') {
      throw runtime_error("Wrong date format: " + date_str);
    }
    in.ignore(1);
  };
  auto ensure_end = [date_str](istream& in) {
    if (in.rdbuf()->in_avail() != 0) {
      throw runtime_error("Wrong date format: " + date_str);
    }
  };

  istringstream ss(date_str);
  int year, month, day;
  ss >> year;
  ensure_and_skip_delimiter(ss);
  ss >> month;
  ensure_and_skip_delimiter(ss);
  ss >> day;
  ensure_end(ss);

  date = {Year{year}, Month{month}, Day{day}};

  return in;
}
ostream& operator<<(ostream& out, const Date& date) {
  out << setw(4) << setfill('0') << date.GetYear() << '-'
      << setw(2) << setfill('0') << date.GetMonth() << '-'
      << setw(2) << setfill('0') << date.GetDay();
  return out;
}
bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    }
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetYear() < rhs.GetYear();
}

class Database {
 public:
  void AddEvent(const Date& date, const string& event) {
    records_[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event) {
    if (records_.count(date) == 0 ||
        records_[date].count(event) == 0) {
      return false;
    }

    records_[date].erase(event);
    if (records_[date].empty()) {
      records_.erase(date);
    }
    return true;
  }

  int DeleteDate(const Date& date) {
    int n = 0;
    if (records_.count(date) == 1) {

      n = static_cast<int>(records_[date].size());
      records_[date].clear();
      records_.erase(date);
    }
    return n;
  }

  [[nodiscard]]
  set<string> Find(const Date& date) const {
    if (records_.count(date) == 1) {
      return records_.at(date);
    }
    return {};
  }

  void Print() const {
    for (auto[date, events] : records_) {
      for (const auto& event : events) {
        cout << date << ' ' << event << endl;
      }
    }
  }

 private:
  map<Date, set<string>> records_;
};

void AddHandle(istream& in, Database& db) {
  Date date;
  in >> date;

  string event;
  in >> event;

  db.AddEvent(date, event);
}
void DelHandle(istream& in, Database& db) {
  Date date;
  in >> date;

  string event;
  in >> event;
  if (event.empty()) {
    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
  } else {
    cout << (db.DeleteEvent(date, event)
             ? "Deleted successfully"
             : "Event not found")
         << endl;
  }

}
void FindHandle(istream& in, const Database& db) {
  Date date;
  in >> date;

  for (const auto& event : db.Find(date)) {
    cout << event << endl;
  }
}

int main() {
  Database db;

  string command;
  try {
    while (getline(cin, command)) {
      stringstream ss(command);

      string operation;
      ss >> operation;

      if (operation.empty()) {
        continue;
      }

      if (operation == "Add") {
        AddHandle(ss, db);

      } else if (operation == "Del") {
        DelHandle(ss, db);

      } else if (operation == "Find") {
        FindHandle(ss, db);

      } else if (operation == "Print") {
        db.Print();

      } else {
        throw runtime_error("Unknown command: " + operation);
      }
    }
  } catch (exception& err) {
    cout << err.what() << endl;
  }
}