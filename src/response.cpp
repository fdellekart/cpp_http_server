#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "fmt/core.h"
#include "response.h"
#include "utils.h"

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

  response.headers->set("Content-Type", ends_with(filepath, ".html")
                                            ? "text/html"
                                            : "text/plain");

  return response;
};

std::string Response::str() {
  std::string response_string = fmt::format("HTTP/1.1 {}\r\n", (int)code);
  std::string formatted_content = fmt::format("{}\r\n", content);
  return response_string + headers->str() + formatted_content;
};

void Response::set_default_headers() {
  headers->set("Content-Length", content.length());
};

Response Response::not_found(std::string message) {
  Response response;
  response.code = StatusCode::NOT_FOUND;
  response.content = message;
  response.set_default_headers();
  return response;
};

Response Response::not_allowed(std::string message) {
  Response response;
  response.code = StatusCode::NOT_ALLOWED;
  response.content = message;
  response.set_default_headers();
  return response;
};
