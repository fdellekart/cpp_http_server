#include <filesystem>
#include <string>
#include <vector>

#include "utils.h"

bool ends_with(std::string string, std::string substring) {
  std::size_t pos = string.find(substring);
  return pos == (string.length() - substring.length());
};

std::vector<fs::path> load_dir_files(std::string target_dir) {
  std::vector<fs::path> files;
  for (const auto &entry : fs::directory_iterator(target_dir))
    files.push_back(entry.path());
  return files;
}