#include "responses.h"

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
  if (r.stop_exist) {
    for (const Bus& bus : r.buses) {
      os << bus << " ";
    }
    os << endl;
  } else {
    os << "No stop" << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
  if (r.bus_exist) {
    for (const auto& stop_to_buses : r.buses_on_stops_for_bus) {
      os << "Stop " << stop_to_buses.first << ": ";
      if (stop_to_buses.second.empty()) {
        os << "no interchange";
      } else {
        for (const Bus& bus : stop_to_buses.second) {
          os << bus << " ";
        }
      }
      os << endl;
    }
  } else {
    os << "No bus" << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
  if (r.buses_exist) {
    for (const auto&[kBus, kStops] : r.buses_to_stops) {
      os << "Bus " << kBus << ": ";
      for (const auto& stop : kStops) {
        os << stop << " ";
      }
      os << endl;
    }
  } else {
    os << "No buses" << endl;
  }
  return os;
}
