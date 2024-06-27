#pragma once

#include <string>
#include <unordered_map>

#include "request.h"
#include "response.h"

class Route {
public:
  typedef std::unordered_map<std::string, std::string> ContextMap;

  Route(HTTP_METHOD method, std::string route,
        void (*request_handler)(Request &, Route &, Response &))
      : method(method), route(route), request_handler(request_handler){};

  HTTP_METHOD method;
  std::string route;
  void (*request_handler)(Request &, Route &, Response &);
  void set_context(std::string key, std::string value) {
    context->insert(std::make_pair(key, value));
  };
  std::string get_context(std::string key) { return context->at(key); };

private:
  ContextMap *context = new ContextMap;
};

class FileGetRoute : public Route {
public:
  FileGetRoute(std::string route, std::string filepath);
};
