#include <iostream>
#include <string>

enum HTTP_VERSION {HTTP1_1=0, HTTP2 };

enum HTTP_METHOD {
  GET=0,
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
  std::string abs_filepath();

private:
  /*Parse http headers from existing request stream

  Assumes that first line of request was already read from
  stream and it can directly start reading the headers.
  */
  void parse_headers(std::stringstream &request_stream);
};
