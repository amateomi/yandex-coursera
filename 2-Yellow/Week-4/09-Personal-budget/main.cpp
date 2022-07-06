/*
 * Реализуйте систему ведения личного бюджета. Вам необходимо обрабатывать
 * запросы следующих типов:
 * - ComputeIncome from to: вычислить чистую прибыль за данный диапазон дат.
 * - Earn from to value: учесть, что за указанный период (равномерно по дням)
 *   была заработана сумма value.
 *
 * Примечания:
 * - Во всех диапазонах from to обе даты from и to включаются.
 *
 * Формат ввода
 * В первой строке вводится количество запросов Q, затем в описанном выше
 * формате вводятся сами запросы, по одному на строке.
 *
 * Формат вывода
 * Для каждого запроса ComputeIncome в отдельной строке выведите вещественное
 * число — прибыль за указанный диапазон дат.
 *
 * Примечание:
 * - используйте std::сout.precision(25)  в вашем коде для единообразия формата
 *   вывода вещественных чисел
 *
 * Ограничения
 * - Количество запросов Q — натуральное число, не превышающее 50.
 * - Все даты вводятся в формате YYYY-MM-DD. Даты корректны (с учётом високосных
 *   годов) и принадлежат интервалу с 2000 до 2099 гг.
 * - value — положительные целые числа, не превышающие 1000000.
 * - 1 секунда на обработку всех запросов.
 */
#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>
#include <chrono>

using namespace std;

pair<string, string> SplitTwoStrict(const string& s, const string& delimiter) {
  const size_t kPos = s.find(delimiter);
  if (kPos == std::string::npos) {
    return {s, ""};
  } else {
    return {s.substr(0, kPos), s.substr(kPos + delimiter.length())};
  }
}

pair<string, string> SplitTwo(const string& s, const string& delimiter) {
  const auto[kLhs, kRhs] = SplitTwoStrict(s, delimiter);
  return {kLhs, kRhs};
}

string ReadToken(string& s, const string& delimiter = " ") {
  const auto[kLhs, kRhs] = SplitTwo(s, delimiter);
  s = kRhs;
  return kLhs;
}

int ConvertToInt(const string& str) {
  size_t pos;
  const int kResult = stoi(string(str), &pos);
  if (pos != str.length()) {
    stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw invalid_argument(error.str());
  }
  return kResult;
}

class Date {
 public:
  static Date FromString(string str) {
    const int kYear = ConvertToInt(ReadToken(str, "-"));
    const int kMonth = ConvertToInt(ReadToken(str, "-"));
    const int kDay = ConvertToInt(str);
    return {kYear, kMonth, kDay};
  }

  [[nodiscard]]
  time_t AsTimestamp() const {
    tm t{};
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_mday = day_;
    t.tm_mon = month_ - 1;
    t.tm_year = year_ - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
  }

 private:
  int year_;
  int month_;
  int day_;

  Date(int year, int month, int day)
      : year_(year), month_(month), day_(day) {}
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
  const time_t kTimestampTo = date_to.AsTimestamp();
  const time_t kTimestampFrom = date_from.AsTimestamp();
  static constexpr int kSecondsInDay = 60 * 60 * 24;
  return static_cast<int>((kTimestampTo - kTimestampFrom) / kSecondsInDay);
}

static const auto kStartDate = Date::FromString("2000-01-01");
static const auto kEndDate = Date::FromString("2100-01-01");
static const size_t kDayCount = ComputeDaysDiff(kEndDate, kStartDate);

int main() {
  cout.precision(25);
  vector<double> money(kDayCount, .0);
  size_t num_queries;
  cin >> num_queries;

  for (size_t i = 0; i < num_queries; ++i) {
    string command, date_from, date_to;
    cin >> command >> date_from >> date_to;
    Date from = Date::FromString(date_from);
    Date to = Date::FromString(date_to);
    auto start_indx = ComputeDaysDiff(from, kStartDate);
    auto finish_indx = ComputeDaysDiff(to, kStartDate);
    if (command == "Earn") {
      double value;
      cin >> value;
      value /= ComputeDaysDiff(to, from) + 1;
      for (int j = start_indx; j <= finish_indx; ++j) {
        money[j] += value;
      }
    } else {
      cout << accumulate(money.begin() + start_indx, money.begin() + finish_indx + 1, 0.) << '\n';
    }
  }

  return 0;
}