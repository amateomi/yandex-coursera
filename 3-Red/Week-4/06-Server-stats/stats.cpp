#include "stats.h"

#include <algorithm>

void Stats::AddMethod(string_view method) {
  if (find(methods_.begin(), methods_.end(), method) != methods_.end()) {
    ++methods_stats_.at(method);
  } else {
    ++methods_stats_.at("UNKNOWN");
  }
}

void Stats::AddUri(string_view uri) {
  if (find(uris_.begin(), uris_.end(), uri) != uris_.end()) {
    ++uri_stats_.at(uri);
  } else {
    ++uri_stats_.at("unknown");
  }
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return methods_stats_;
}

const map<string_view, int>& Stats::GetUriStats() const {
  return uri_stats_;
}

HttpRequest ParseRequest(string_view line) {
  HttpRequest http_request;

  line.remove_prefix(line.find_first_not_of(' '));

  size_t space = line.find(' ');
  http_request.method = line.substr(0, space);
  line.remove_prefix(space + 1);

  space = line.find(' ');
  http_request.uri = line.substr(0, space);

  line.remove_prefix(space + 1);
  http_request.protocol = line;

  return http_request;
}
