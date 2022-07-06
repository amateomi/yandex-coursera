/*
 * В курсе «Белый пояс по С++» у нас была задача «Автобусные остановки — 1». В
 * этой задаче вам будет дано её правильное решение, целиком содержащееся внутри
 * функции main. Вам надо будет выполнить декомпозицию этого решения на заранее
 * заданные блоки так, чтобы получившаяся программа так же корректно решала
 * задачу. Условие задачи «Автобусные остановки — 1» приведено ниже.
 */
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

using Stop = string;
using Bus = string;

struct Query {
  QueryType type = QueryType::NewBus;
  Bus bus;
  Stop stop;
  vector<Stop> stops;
};

istream& operator>>(istream& is, Query& q) {
  string operation_code;
  is >> operation_code;
  if (operation_code == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    q.stops.resize(stop_count);
    for (Stop& stop : q.stops) {
      is >> stop;
    }

  } else if (operation_code == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;

  } else if (operation_code == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;

  } else if (operation_code == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  bool stop_exist;
  vector<Bus> buses;
};

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

struct StopsForBusResponse {
  bool bus_exist;
  vector<pair<Stop, vector<Bus>>> buses_on_stops_for_bus;
};

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

struct AllBusesResponse {
  bool buses_exist;
  map<Bus, vector<Stop>> buses_to_stops;
};

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

class BusManager {
 public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops_[bus] = stops;
    for (const string& stop : stops) {
      stops_to_buses_[stop].push_back(bus);
    }
  }

  [[nodiscard]]
  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (stops_to_buses_.count(stop) == 0) {
      return {false};
    }
    return {true, stops_to_buses_.at(stop)};
  }

  [[nodiscard]]
  StopsForBusResponse GetStopsForBus(const string& bus) const {
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

  [[nodiscard]]
  AllBusesResponse GetAllBuses() const {
    if (buses_to_stops_.empty()) {
      return {false};
    }
    return {true, buses_to_stops_};
  }

 private:
  map<Bus, vector<Stop>> buses_to_stops_;
  map<Stop, vector<Bus>> stops_to_buses_;
};

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
      case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
      case QueryType::BusesForStop:
        cout << bm.GetBusesForStop(q.stop) << endl;
        break;
      case QueryType::StopsForBus:
        cout << bm.GetStopsForBus(q.bus) << endl;
        break;
      case QueryType::AllBuses:
        cout << bm.GetAllBuses() << endl;
        break;
    }
  }
}