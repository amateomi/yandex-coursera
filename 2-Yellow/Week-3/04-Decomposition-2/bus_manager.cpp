#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  buses_to_stops_[bus] = stops;
  for (const string& stop : stops) {
    stops_to_buses_[stop].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  if (stops_to_buses_.count(stop) == 0) {
    return {false};
  }
  return {true, stops_to_buses_.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  if (buses_to_stops_.count(bus) == 0) {
    return {false};
  }
  StopsForBusResponse result{true};
  for (const Stop& stop : buses_to_stops_.at(bus)) {
    result.buses_on_stops_for_bus.push_back({stop, {}});
    if (stops_to_buses_.at(stop).size() > 1) {
      for (const Bus& other_bus : stops_to_buses_.at(stop)) {
        if (other_bus != bus) {
          result.buses_on_stops_for_bus.back().second.push_back(other_bus);
        }
      }
    }
  }
  return result;
}

AllBusesResponse BusManager::GetAllBuses() const {
  if (buses_to_stops_.empty()) {
    return {false};
  }
  return {true, buses_to_stops_};
}
