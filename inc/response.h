#pragma once

#include <iostream>
#include <map>
#include <string>

#include "headers.h"
#include "utils.h"

enum StatusCode { OK = 200, NOT_FOUND = 404, NOT_ALLOWED = 405 };

class Response {
public:
  StatusCode code;
  HeaderCollection *headers = new HeaderCollection;
  std::string content;
  std::string str();

  // Response 404 not found if the route does not exist
  static Response not_found(std::string mesage);

  // Response 405 not allowed if route exists but method is unsupported
  static Response not_allowed(std::string message);

  static Response from_file(std::string filepath);
  /*
  Fill the following headers with default values:
    - Content-Length
  */
  void set_default_headers();
};