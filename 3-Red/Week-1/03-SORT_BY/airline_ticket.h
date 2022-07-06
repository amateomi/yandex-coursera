#ifndef INC_03__SORT_BY__AIRLINE_TICKET_H_
#define INC_03__SORT_BY__AIRLINE_TICKET_H_

#include <string>
using namespace std;

struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};

#endif //INC_03__SORT_BY__AIRLINE_TICKET_H_
