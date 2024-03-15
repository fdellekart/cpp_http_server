#include <iostream>
#include <string>

enum HTTP_VERSION { VERSION_UNDEFINED, HTTP1_1, HTTP2 };

enum HTTP_METHOD {
  METHOD_UNDEFINED,
  GET,
  POST,
};

// Get a string representing the method name
std::string string_from_method(HTTP_METHOD method);

struct Request {
public:
  HTTP_VERSION version;
  HTTP_METHOD method;
  std::string path;
  std::map<std::string, std::string> headers;

  void parse_string(std::string &request);

private:
  /*Parse http headers from existing request stream

  Assumes that first line of request was already read from
  stream and it can directly start reading the headers.
  */
  void parse_headers(std::stringstream &request_stream);
};
