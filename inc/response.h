#include <iostream>
#include <string>

enum StatusCode { OK = 200, NOT_FOUND = 404 };

class Response {
public:
  StatusCode code;
  std::string content;
  std::string str();
  static Response from_file(std::string filepath);
};