/*
 * Напишите макрос UPDATE_FIELD.
 */
#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

bool operator==(const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
  return !(lhs == rhs);
}

ostream& operator<<(ostream& os, const Date& date) {
  os << date.year << '.' << date.month << '.' << date.day;
  return os;
}

istream& operator>>(istream& is, Date& date) {
  is >> date.year;
  is.ignore();
  is >> date.month;
  is.ignore();
  is >> date.day;
  return is;
}

bool operator==(const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

bool operator!=(const Time& lhs, const Time& rhs) {
  return !(lhs == rhs);
}

ostream& operator<<(ostream& os, const Time& time) {
  os << time.hours << ':' << time.minutes;
  return os;
}

istream& operator>>(istream& is, Time& time) {
  is >> time.hours;
  is.ignore();
  is >> time.minutes;
  return is;
}

bool operator!=(const AirlineTicket& lhs, const AirlineTicket& rhs) {
  return tie(lhs.from, lhs.to, lhs.airline,
             lhs.departure_date, lhs.departure_time,
             lhs.arrival_date, lhs.arrival_time, lhs.price)
      !=
          tie(rhs.from, rhs.to, rhs.airline,
              rhs.departure_date, rhs.departure_time,
              rhs.arrival_date, rhs.arrival_time, rhs.price);
}

ostream& operator<<(ostream& os, const AirlineTicket& airline_ticket) {
  return os;
}

#define UPDATE_FIELD(ticket, field, values) { \
  auto it = (values).find(#field);            \
  if (it != (values).end()) {                 \
    istringstream is(it->second);             \
    is >> (ticket).field;                     \
  }                                           \
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates_1 = {
      {"departure_date", "2018-2-28"},
      {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates_1);
  UPDATE_FIELD(t, departure_time, updates_1);
  UPDATE_FIELD(t, price, updates_1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates_2 = {
      {"price", "12550"},
      {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates_2);
  UPDATE_FIELD(t, departure_time, updates_2);
  UPDATE_FIELD(t, arrival_time, updates_2);
  UPDATE_FIELD(t, price, updates_2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}

