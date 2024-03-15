#include <filesystem>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#include "connection.h"
#include "server.h"

using namespace std;
namespace fs = std::filesystem;

// Load all files located in the given directory
std::vector<fs::path> load_dir_files(std::string target_dir) {
  std::vector<fs::path> files;
  for (const auto &entry : fs::directory_iterator(target_dir))
    files.push_back(entry.path());
  return files;
}

HttpServer::HttpServer(uint16_t port, std::string target_dir)
    : port(port), target_dir(target_dir) {
  opt = 1;
  files = load_dir_files(target_dir);

  init_address();
}

int HttpServer::run() {
  printf("Starting server. Listening on port %u.\n\n", port);
  init_socket();

  while (1) {
    if ((new_socket =
             accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
      perror("accept failed");
      exit(EXIT_FAILURE);
    }
    ConnHandler *handler = new ConnHandler;
    handler->dispatch_handler_thread(new_socket);
  }

  close(server_fd);
  return 0;
}

void HttpServer::init_address() {
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  addrlen = sizeof(address);
}

void HttpServer::init_socket() {
  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
}
