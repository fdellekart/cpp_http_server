#include <iostream>
#include <map>
#include <string>

#include "headers.h"

enum StatusCode { OK = 200, NOT_FOUND = 404 };

class Response {
public:
  StatusCode code;
  HeaderCollection *headers = new HeaderCollection;
  std::string content;
  std::string str();

  static Response from_file(std::string filepath);
  /*
  Fill the following headers with default values:
    - Content-Length
  */
  void set_default_headers();
};