#include <string>

bool ends_with(std::string string, std::string substring) {
  std::size_t pos = string.find(substring);
  return pos == (string.length() - substring.length());
};