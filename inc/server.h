#include <filesystem>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <vector>

#include "connection.h"
#include "request.h"
#include "response.h"

#define RoutesMapT std::map<std::string, std::map<HTTP_METHOD, Route>>

namespace fs = std::filesystem;

class HttpServer {
public:
  HttpServer(uint16_t port);

  int run();

  /* Register a route to be available from the server */
  void register_route(Route route);

protected:
  uint16_t port;

private:
  int server_fd, new_socket, opt;
  sockaddr_in address;
  socklen_t addrlen;
  void init_address();
  // Run the HttpServer::handle method in a detached thread
  void dispatch_handler_thread(Connection &connection);

  // Create the socket file descriptor listen for connections
  void init_socket();

  // Files in the target directory
  std::vector<fs::path> files;

  /* Read a request from the socket and process it

  If request is invalid then return an appropriate
  status code and error message, else invoke the route
  handler and reply with the response.
  */
  void handle(Connection connection);

  RoutesMapT *routes = new RoutesMapT;
};