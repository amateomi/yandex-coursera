#include "date.h"

Date::Date(int year, int month, int day)
    : year_(year),
      month_(month),
      day_(day) {}

Date ParseDate(istream& is) {
  int year;
  is >> year;
  is.ignore(1);

  int month;
  is >> month;
  is.ignore(1);

  int day;
  is >> day;
  is.ignore(1);

  return {year, month, day};
}

bool operator==(const Date& lhs, const Date& rhs) {
  return tie(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())
      == tie(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator!=(const Date& lhs, const Date& rhs) {
  return !(rhs == lhs);
}

bool operator<(const Date& lhs, const Date& rhs) {
  return tie(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())
      < tie(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>(const Date& lhs, const Date& rhs) {
  return rhs < lhs;
}

bool operator<=(const Date& lhs, const Date& rhs) {
  return !(rhs < lhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
  return !(lhs < rhs);
}

ostream& operator<<(ostream& os, const Date& date) {
  os << setw(4) << setfill('0') << date.GetYear() << '-'
     << setw(2) << setfill('0') << date.GetMonth() << '-'
     << setw(2) << setfill('0') << date.GetDay();
  return os;
}
