#include<iostream>
#include<string.h>

#include<request_handler.h>

std::string RequestHandler::process(std::string request) {
    printf("%s\n", request.c_str());
    return std::string("Hello from server");
}
