#pragma once

#include <map>
#include <string>

class HeaderCollection {
public:
  typedef std::map<std::string, std::string> HeaderMap;

  // Combine all headers into a string with <key>:<value> pairs separated by
  // \r\n
  std::string str();

  // Set a header
  void set(std::string key, std::string value);
  // Transform integer int string and set it
  void set(std::string key, int value);

  // Get a header
  std::string get(std::string value);

private:
  HeaderMap *headers = new HeaderMap;
};
