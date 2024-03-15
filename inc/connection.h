#pragma once
#include <string>

class ConnHandler {
public:
  void dispatch_handler_thread(int socket);

private:
  // Read four bytes for the message length and cast to uint32_t
  uint32_t read_msg_len(int socket);
  // Read a message from client
  std::string read_msg(int socket);
  void handle(int socket);
  // Process the request and return a response
  std::string process_request(std::string &request);
};