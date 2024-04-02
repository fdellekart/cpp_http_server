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

void ConnHandler::dispatch_handler_thread(int socket) {
  std::thread handler_thread(&ConnHandler::handle, this, socket);
  handler_thread.detach();
}

void ConnHandler::handle(int socket) {
  std::string recv_message = read_msg(socket);
  std::string response = process_request(recv_message);
  send(socket, response.c_str(), strlen(response.c_str()), 0);
  close(socket);
}

std::string ConnHandler::process_request(std::string &request_string) {
  Request request;
  request.parse_string(request_string);

  std::string filepath = "./files";
  filepath += request.path;

  printf("Received Request\n");
  printf("--------------------------\n");
  request.print();

  Response response = Response::from_file(filepath);

  response.headers->set("Content-Length", response.content.length());

  return response.str();
}

std::string ConnHandler::read_msg(int socket) {
  std::string recv_message(MAX_REQUEST_SIZE, 0);
  read(socket, &recv_message[0], MAX_REQUEST_SIZE);
  return recv_message;
}