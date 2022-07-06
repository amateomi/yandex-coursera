#ifndef DATABASE__DATE_H_
#define DATABASE__DATE_H_

#include <sstream>
#include <iomanip>

using namespace std;

class Date {
 public:
  Date(int year, int month, int day);

  [[nodiscard]] const int& GetYear() const { return year_; }
  [[nodiscard]] const int& GetMonth() const { return month_; }
  [[nodiscard]] const int& GetDay() const { return day_; }

 private:
  const int year_ = 0;
  const int month_ = 1;
  const int day_ = 1;
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

Date ParseDate(istream& is);

ostream& operator<<(ostream& os, const Date& date);

#endif //DATABASE__DATE_H_
