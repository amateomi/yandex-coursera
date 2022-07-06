#ifndef INC_06__SERVER_STATS__STATS_H_
#define INC_06__SERVER_STATS__STATS_H_

#include "http_request.h"

#include <string>
#include <string_view>
#include <array>
#include <map>

using namespace std;

class Stats {
 public:
  Stats() {
    for (const auto& method : methods_) {
      methods_stats_[method] = 0;
    }
    for (const auto& uri : uris_) {
      uri_stats_[uri] = 0;
    }
  }

  void AddMethod(string_view method);
  void AddUri(string_view uri);

  [[nodiscard]] const map<string_view, int>& GetMethodStats() const;
  [[nodiscard]] const map<string_view, int>& GetUriStats() const;

 private:
  const array<string, 5> methods_ = {
      "GET",
      "POST",
      "PUT",
      "DELETE",
      "UNKNOWN"
  };

  const array<string, 6> uris_ = {
      "/",
      "/order",
      "/product",
      "/basket",
      "/help",
      "unknown"
  };

  map<string_view, int> methods_stats_;
  map<string_view, int> uri_stats_;
};

HttpRequest ParseRequest(string_view line);

#endif //INC_06__SERVER_STATS__STATS_H_
