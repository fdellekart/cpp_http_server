#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
