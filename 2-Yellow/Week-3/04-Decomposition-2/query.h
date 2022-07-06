#ifndef INC_04__DECOMPOSITION_2__QUERY_H_
#define INC_04__DECOMPOSITION_2__QUERY_H_

#include <istream>
#include <vector>

using namespace std;

using Stop = string;
using Bus = string;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type = QueryType::NewBus;
  Bus bus;
  Stop stop;
  vector<Stop> stops;
};

istream& operator>>(istream& is, Query& q);

#endif //INC_04__DECOMPOSITION_2__QUERY_H_
