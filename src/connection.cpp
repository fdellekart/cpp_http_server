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
#include "server.h"

void Connection::reply(Response &response) {
  std::string str_response = response.str();
  send(socket, str_response.c_str(), strlen(str_response.c_str()), 0);
  close(socket);
}

int Connection::read_request(Request &request) {
  char recv_message[MAX_REQUEST_SIZE] = {0};
  int buf_idx = 0;

  do {
    read(socket, recv_message + buf_idx, 1);
    buf_idx++;
  } while (strcmp(recv_message + buf_idx - 4, "\r\n\r\n") != 0 &
           buf_idx < MAX_REQUEST_SIZE);

  if (buf_idx == MAX_REQUEST_SIZE) {
    return -1;
  } else {
    std::string rcv_str = recv_message;
    request.parse_string(rcv_str);
    return buf_idx;
  }
}