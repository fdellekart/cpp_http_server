#pragma once

#include <iostream>
#include <map>
#include <string>

#include "headers.h"
#include "utils.h"

enum StatusCode { OK = 200, NOT_FOUND = 404 };

class Response {
public:
  StatusCode code;
  HeaderCollection *headers = new HeaderCollection;
  std::string content;
  std::string str();

  static Response not_found(std::string mesage);

  static Response from_file(std::string filepath);
  /*
  Fill the following headers with default values:
    - Content-Length
  */
  void set_default_headers();
};