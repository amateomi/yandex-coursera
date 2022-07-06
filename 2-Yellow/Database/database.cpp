#include "database.h"

void Database::Add(const Date& date, const string& event) {
  auto& events = records_[date];

  const bool is_added = events.ordered.insert(event).second;
  if (is_added) {
    events.unordered.push_back(event);
  }
}

void Database::Print(ostream& os) const {
  for (const auto&[date, events] : records_) {
    for (const auto& event : events.unordered) {
      PrintRecord(os, date, event);
      os << endl;
    }
  }
}

int Database::RemoveIf(const Database::Predicate& predicate) {
  int count = 0;

  vector<Date> dates_to_delete;
  dates_to_delete.reserve(records_.size());
  for (auto& date_and_events : records_) {
    auto& date = date_and_events.first;
    auto& events = date_and_events.second;

    auto predicate_match = [predicate, date](const string& event) {
      return predicate(date, event);
    };
    auto predicate_not_match = [predicate_match](const string& event) {
      return !predicate_match(event);
    };

    // Put matching events at the end
    const auto& border = stable_partition(events.unordered.begin(),
                                          events.unordered.end(),
                                          predicate_not_match);
    // Amount of matching events
    const auto size = distance(border, events.unordered.end());
    for (int i = 0; i < size; ++i) {
      // Erase events in set
      events.ordered.erase(events.unordered.back());
      // Erase events in vector
      events.unordered.pop_back();
    }

    if (events.unordered.empty()) {
      dates_to_delete.push_back(date);
    }

    count += static_cast<int>(size);
  }

  for (const auto& date : dates_to_delete) {
    records_.erase(date);
  }

  return count;
}

vector<string> Database::FindIf(const Database::Predicate& predicate) const {
  vector<string> entries;
  for (const auto& date_and_events : records_) {
    const auto& date = date_and_events.first;
    const auto& events = date_and_events.second;

    for (const auto& event : events.unordered) {
      if (predicate(date, event)) {
        ostringstream ss;
        PrintRecord(ss, date, event);
        entries.push_back(ss.str());
      }
    }
  }
  return entries;
}

string Database::Last(Date date) const {
  auto it = records_.upper_bound(date);
  if (it == records_.begin()) {
    throw invalid_argument("No entries");
  }
  it = prev(it);

  const auto&[date_to_print, events] = *it;
  const string& event_to_print = events.unordered.back();

  ostringstream ss;
  PrintRecord(ss, date_to_print, event_to_print);
  return ss.str();
}

void Database::PrintRecord(ostream& os,
                           const Date& date,
                           const string& event) {
  os << date << ' ' << event;
}
