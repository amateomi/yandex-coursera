#ifndef INC_06__SERVER_STATS__HTTP_REQUEST_H_
#define INC_06__SERVER_STATS__HTTP_REQUEST_H_

#include <string_view>
using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;
};

#endif //INC_06__SERVER_STATS__HTTP_REQUEST_H_
