#pragma once
#include <string>

#include "request.h"
#include "response.h"

class Connection {
public:
  Connection(int socket) : socket(socket){};
  int socket;
  void reply(Response &response);
  void read_request(Request &request);
};
