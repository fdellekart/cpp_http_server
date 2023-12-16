#include<iostream>
#include "server.h"
#include "connection.h"
#include "request_handler.h"

#define PORT 8080

using namespace std;

int main(int argc, char* argv[]) {
    RequestHandler request_handler;
    ConnHandler handler(request_handler);
    HttpServer server(PORT, handler);
    server.run();
    return 0;
}
