#pragma once
#include <string>

#include "request.h"
#include "response.h"

class Connection {
public:
  Connection(int socket) : socket(socket){};
  int socket;
  void reply(Response &response);

  /// @brief Read from connection and parse data into Request
  /// @param request request object reference to put data  in
  /// @return nr of bytes read or -1 on if max length exceeded
  int read_request(Request &request);
};
