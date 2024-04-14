#include <string>

#include "request.h"
#include "response.h"

class Route {
public:
  Route(HTTP_METHOD method, std::string route,
        Response (*request_handler)(Request))
      : method(method), route(route), request_handler(request_handler){};

  HTTP_METHOD method;
  std::string route;
  Response (*request_handler)(Request);

  static Route file(std::string filepath);
};
