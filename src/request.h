#include<iostream>


enum HTTP_VERSION {
    VERSION_UNDEFINED,
    HTTP1_1,
    HTTP2
};

enum HTTP_METHOD {
    METHOD_UNDEFINED,
    GET,
    POST,
};

struct Request {
    HTTP_VERSION version;
    HTTP_METHOD method;
    std::string path;
    
    void parse_string(std::string request);
};
