#pragma once
#include <string>

#include "request.h"
#include "response.h"

class Connection {
public:
  Connection(int socket) : socket(socket){};
  int socket;
  void reply(Response &response);
  Request read_request();
};

/// @brief Check if the last four bytes read from request are two CRLF
/// @param message pointer to the receiving message array
/// @param buf_idx current number of bytes read
/// @return boolean indicating if the request is finished
bool terminate_read(char* message, int buff_idx);