#include <iostream>
#include <map>
#include <string>

enum StatusCode { OK = 200, NOT_FOUND = 404 };

class Response {
public:
  StatusCode code;
  std::string content;
  std::string str();
  void set_header(std::string key, std::string value);
  void set_header(std::string key, std::size_t value);

  static Response from_file(std::string filepath);

private:
  std::map<std::string, std::string> *headers =
      new std::map<std::string, std::string>;
  // Combine headers into <key>: <value>\r\n string for returning
  std::string get_headers_string();
};