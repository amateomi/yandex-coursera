#ifndef DATABASE__DATABASE_H_
#define DATABASE__DATABASE_H_

#include "date.h"

#include <functional>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Database {
 public:
  struct Events {
    vector<string> unordered;
    set<string> ordered;
  };

  using Predicate = function<bool(const Date&, const string&)>;

  void Add(const Date& date, const string& event);

  void Print(ostream& os) const;

  int RemoveIf(const Predicate& predicate);

  [[nodiscard]] vector<string> FindIf(const Predicate& predicate) const;

  [[nodiscard]] string Last(Date date) const;

 private:
  static void PrintRecord(ostream& os, const Date& date, const string& event);

  // Set is used for speed up Add() and Last() execution time
  map<Date, Events> records_;
};

#endif //DATABASE__DATABASE_H_
