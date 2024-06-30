#include <fmt/core.h>
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

HttpServer::HttpServer(uint16_t port) : port(port) {
  opt = 1;
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
    Connection connection(new_socket);
    dispatch_handler_thread(connection);
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

void HttpServer::register_route(Route route) {
  auto existing_routes = routes->find(route.route);
  if (existing_routes == routes->end()) {
    auto new_routes = new std::map<HTTP_METHOD, Route>;
    new_routes->insert(std::make_pair(route.method, route));
    routes->insert(std::make_pair(route.route, *new_routes));
  } else {
    existing_routes->second.insert(std::make_pair(route.method, route));
  };
};

void HttpServer::handle(Connection connection) {
  auto request = std::unique_ptr<Request>{new Request};
  auto response = std::unique_ptr<Response>{new Response};
  
  if (connection.read_request(*request) < 0) {
    response->payload_too_large(fmt::format(
        "Request too long. Maximum size {} bytes.", MAX_REQUEST_SIZE));
    connection.reply(*response);
    return;
  };
  auto methods = routes->find(request->path);

  // Route does not exist
  if (methods == routes->end()) {
    response->not_found(
        fmt::format("Route '{}' does not exist!", request->path));
    // Route exists but method is not defined
  } else if (methods->second.find(request->method) == methods->second.end()) {
    response->not_allowed(fmt::format("Route '{}' does not support method '{}'",
                                      request->path,
                                      string_from_method(request->method)));
  } else {
    auto route = routes->at(request->path).at(request->method);
    route.request_handler(*request, route, *response);
  };

  connection.reply(*response);
};

void HttpServer::dispatch_handler_thread(Connection &connection) {
  std::thread handler_thread(&HttpServer::handle, this, connection);
  handler_thread.detach();
};
