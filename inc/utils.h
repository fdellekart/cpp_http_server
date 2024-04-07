#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

/*Check if a string ends with another string.

@param string: String to check
@param substring: Substring to compare to end of string
*/
bool ends_with(std::string string, std::string substring);

// Load all files located in the given directory
std::vector<fs::path> load_dir_files(std::string target_dir);
