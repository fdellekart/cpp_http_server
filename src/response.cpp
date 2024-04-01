#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "fmt/core.h"
#include "response.h"

Response Response::from_file(std::string filepath) {
  Response response;

  std::ifstream input_file(filepath);

  if (!input_file.good()) {
    response.code = StatusCode::NOT_FOUND;
  } else {
    std::stringstream file_buffer;
    file_buffer << input_file.rdbuf();

    response.code = StatusCode::OK;
    response.content = file_buffer.str();
  }

  input_file.close();

  (*response.headers)["Content-Type"] = "text/html";

  return response;
};

std::string Response::str() {
  std::string response_string = fmt::format("HTTP/1.1 {}\r\n", (int)code);
  std::string headers_string = get_headers_string();
  std::string formatted_content = fmt::format("{}\r\n", content);
  return response_string + headers_string + formatted_content;
};

std::string Response::get_headers_string() {
  std::string result;
  std::string header_line;

  std::map<std::string, std::string>::iterator iter;
  for (iter = (*headers).begin(); iter != (*headers).end(); ++iter) {
    header_line = fmt::format("{}: {}\r\n", iter->first, iter->second);
    result += header_line;
    header_line.clear();
  };

  return result;
};