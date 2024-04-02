#include <fmt/core.h>
#include <string>

#include "headers.h"

void HeaderCollection::set(std::string key, std::string value) {
  (*headers)[key] = value;
};

void HeaderCollection::set(std::string key, int value) {
  (*headers)[key] = fmt::format("{}", value);
};

std::string HeaderCollection::get(std::string key) { return headers->at(key); }

std::string HeaderCollection::str() {
  std::string result;
  std::string header_line;

  std::map<std::string, std::string>::iterator iter;
  for (iter = (*headers).begin(); iter != (*headers).end(); ++iter) {
    header_line = fmt::format("{}: {}\r\n", iter->first, iter->second);
    result += header_line;
    header_line.clear();
  }

  return result + "\r\n";
}