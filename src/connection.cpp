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
#define MAX_REQUEST_SIZE 1024 * 100 // 100 kB

/// @brief Check if the last four bytes read from request are two CRLF
/// @param message pointer to the receiving message array
/// @param buf_idx current number of bytes read
/// @return boolean indicating if the request is finished
bool terminate_read(char *message, int buf_idx) {
  return message[buf_idx - 3] == '\r' & message[buf_idx - 2] == '\n' &
         message[buf_idx - 1] == '\r' & message[buf_idx] == '\n';
}

void Connection::reply(Response &response) {
  std::string str_response = response.str();
  send(socket, str_response.c_str(), strlen(str_response.c_str()), 0);
  close(socket);
}

Request Connection::read_request() {
  char recv_message[MAX_REQUEST_SIZE] = {0};
  int buf_idx = -1;

  do {
    buf_idx++;
    read(socket, &recv_message[buf_idx], 1);
  } while (!terminate_read(recv_message, buf_idx));

  std::string rcv_str = recv_message;
  Request request;
  request.parse_string(rcv_str);
  return request;
}