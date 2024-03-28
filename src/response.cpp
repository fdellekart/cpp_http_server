#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "response.h"

Response Response::from_file(std::string filepath, StatusCode code) {
  std::stringstream file_buffer;
  std::ifstream input_file(filepath);
  file_buffer << input_file.rdbuf();

  Response response;
  response.code = code;
  response.content = file_buffer.str();

  return response;
};

std::string Response::str() {
  std::string response_string("");
  response_string += "HTTP/1.1";
  response_string += " ";
  response_string += code;
  response_string += "\r\n";
  return response_string;
};
