#include<iostream>
#include "server.h"
#include "connection.h"

#define PORT 8080

using namespace std;

int main(int argc, char* argv[]) {
    ConnHandler handler;
    HttpServer server(PORT, handler);
    server.run();
    return 0;
}
