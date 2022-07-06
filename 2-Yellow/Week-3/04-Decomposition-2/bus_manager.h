#ifndef INC_04__DECOMPOSITION_2__BUS_MANAGER_H_
#define INC_04__DECOMPOSITION_2__BUS_MANAGER_H_

#include "responses.h"

using namespace std;

using Stop = string;
using Bus = string;

class BusManager {
 public:
  void AddBus(const string& bus, const vector<string>& stops);

  [[nodiscard]]
  BusesForStopResponse GetBusesForStop(const string& stop) const;

  [[nodiscard]]
  StopsForBusResponse GetStopsForBus(const string& bus) const;

  [[nodiscard]]
  AllBusesResponse GetAllBuses() const;

 private:
  map<Bus, vector<Stop>> buses_to_stops_;
  map<Stop, vector<Bus>> stops_to_buses_;
};

#endif //INC_04__DECOMPOSITION_2__BUS_MANAGER_H_
