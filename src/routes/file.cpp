#include <fstream>
#include <string>

#include "fmt/core.h"

#include "response.h"
#include "routes.h"

void file_request_handler(Request &request, FileGetRoute &route,
                          Response &response) {
  printf("Received Request\n");
  printf("--------------------------\n");
  request.print();

  response.from_file(route.get_context("filepath"));
  response.set_default_headers();
};

FileGetRoute::FileGetRoute(std::string route, std::string filepath)
    : Route(HTTP_METHOD::GET, route,
            (void(*)(Request &, Route &, Response &)) &
                file_request_handler) {
  std::ifstream file(filepath);
  if (!file.good()) {
    throw fmt::format("File '{}' does not exist. Cannot create route.",
                      filepath);
  }
  file.close();
  set_context("filepath", filepath);
};
