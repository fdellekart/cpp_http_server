#include <filesystem>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <vector>

#include "connection.h"
#include "request.h"
#include "response.h"

#define RoutesMapT std::map<std::string, Route>

namespace fs = std::filesystem;

class Route {
public:
  Route(HTTP_METHOD method, std::string route,
        Response (*request_handler)(Request))
      : method(method), route(route), request_handler(request_handler){};

  HTTP_METHOD method;
  std::string route;
  Response (*request_handler)(Request);
};

class HttpServer {
public:
  HttpServer(uint16_t port, std::string target_dir);

  int run();
  void register_route(Route route);
  void dispatch_handler_thread(Connection &connection);

  uint16_t port;
  std::string target_dir;

private:
  int server_fd, new_socket, opt;
  sockaddr_in address;
  socklen_t addrlen;
  void init_address();

  // Create the socket file descriptor listen for connections
  void init_socket();

  // Files in the target directory
  std::vector<fs::path> files;

  void handle(Connection connection);

  RoutesMapT *routes = new RoutesMapT;
};