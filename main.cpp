#include "connection.h"
#include "routes.h"
#include "server.h"
#include <iostream>
#include <string>

#define PORT 8080

using namespace std;

int main(int argc, char *argv[]) {
  HttpServer server(PORT);

  FileGetRoute hello_route("/hello_world.html", "./files/hello_world.html");

  server.register_route(hello_route);
  server.run();
  return 0;
};
