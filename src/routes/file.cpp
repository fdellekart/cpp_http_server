#include <fstream>
#include <string>

#include "fmt/core.h"

#include "routes.h"

Response file_request_handler(Request &request, FileGetRoute &route) {
  printf("Received Request\n");
  printf("--------------------------\n");
  request.print();

  Response response = Response::from_file(route.filepath);
  response.set_default_headers();
  return response;
};

FileGetRoute::FileGetRoute(std::string route, std::string filepath)
    : Route(HTTP_METHOD::GET, route, nullptr), filepath(filepath) {
  std::ifstream file(filepath);
  if (!file.good()) {
    throw fmt::format("File '{}' does not exist. Cannot create route.",
                      filepath);
  }
  file.close();
  request_handler = (Response (*)(Request&, Route&))&file_request_handler;
};
