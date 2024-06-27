#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "fmt/core.h"
#include "response.h"
#include "utils.h"

void Response::from_file(std::string filepath) {
  std::ifstream input_file(filepath);

  if (!input_file.good()) {
    code = StatusCode::NOT_FOUND;
  } else {
    std::stringstream file_buffer;
    file_buffer << input_file.rdbuf();

    code = StatusCode::OK;
    content = file_buffer.str();
  }

  input_file.close();

  headers->set("Content-Type",
               ends_with(filepath, ".html") ? "text/html" : "text/plain");
};

std::string Response::str() {
  std::string response_string = fmt::format("HTTP/1.1 {}\r\n", (int)code);
  std::string formatted_content = fmt::format("{}\r\n", content);
  return response_string + headers->str() + formatted_content;
};

void Response::set_default_headers() {
  headers->set("Content-Length", content.length());
};

void Response::not_found(std::string message) {
  code = StatusCode::NOT_FOUND;
  content = message;
  set_default_headers();
};

void Response::not_allowed(std::string message) {
  code = StatusCode::NOT_ALLOWED;
  content = message;
  set_default_headers();
};
