#include "connection.h"
#include "server.h"
#include <iostream>
#include <string>

#define PORT 8080

using namespace std;

Response handle_hello_world_request(Request request) {
  std::string filepath = "./files";
  filepath += request.path;

  printf("Received Request\n");
  printf("--------------------------\n");
  request.print();

  Response response = Response::from_file(filepath);
  response.set_default_headers();
  return response;
};

int main(int argc, char *argv[]) {
  HttpServer server(PORT);

  Route hello_route =
      Route(HTTP_METHOD::GET, "/hello_world.html", &handle_hello_world_request);

  server.register_route(hello_route);
  server.run();
  return 0;
};
