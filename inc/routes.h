#pragma once

#include <string>
#include <unordered_map>

#include "request.h"
#include "response.h"

#define ContextType std::unordered_map<std::string, std::string>

class Route {
public:
  Route(HTTP_METHOD method, std::string route,
        Response (*request_handler)(Request &, Route &))
      : method(method), route(route), request_handler(request_handler){};

  HTTP_METHOD method;
  std::string route;
  Response (*request_handler)(Request &, Route &);
  void set_context(std::string key, std::string value) {
    context->insert(std::make_pair(key, value));
  };
  std::string get_context(std::string key) { return context->at(key); };

private:
  ContextType *context = new ContextType;
};

class FileGetRoute : public Route {
public:
  FileGetRoute(std::string route, std::string filepath);
};
