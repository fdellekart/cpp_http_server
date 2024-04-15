#pragma once

#include <string>

#include "request.h"
#include "response.h"

class Route {
public:
  Route(HTTP_METHOD method, std::string route,
        Response (*request_handler)(Request &, Route &))
      : method(method), route(route), request_handler(request_handler){};

  HTTP_METHOD method;
  std::string route;
  Response (*request_handler)(Request &, Route &);
};

class FileGetRoute : public Route {
public:
  FileGetRoute(std::string route, std::string filepath);
  std::string filepath;
};
