#ifndef INC_04__DECOMPOSITION_2__RESPONSES_H_
#define INC_04__DECOMPOSITION_2__RESPONSES_H_

#include <ostream>
#include <vector>
#include <map>

using namespace std;

using Stop = string;
using Bus = string;

struct BusesForStopResponse {
  bool stop_exist;
  vector<Bus> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  bool bus_exist;
  vector<pair<Stop, vector < Bus>>> buses_on_stops_for_bus;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  bool buses_exist;
  map<Bus, vector<Stop>> buses_to_stops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r);

#endif //INC_04__DECOMPOSITION_2__RESPONSES_H_
