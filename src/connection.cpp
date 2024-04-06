#include <fstream>
#include <iostream>
#include <thread>

#include <bits/stdc++.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "connection.h"
#include "request.h"
#include "response.h"

// Number of bytes read from socket per request
#define MAX_REQUEST_SIZE 1024

void Connection::reply(Response &response) {
  std::string str_response = response.str();
  send(socket, str_response.c_str(), strlen(str_response.c_str()), 0);
  close(socket);
}

Request Connection::read_request() {
  std::string recv_message(MAX_REQUEST_SIZE, 0);
  read(socket, &recv_message[0], MAX_REQUEST_SIZE);
  Request request;
  request.parse_string(recv_message);
  return request;
}