#include<iostream>
#include "server.h"

#define PORT 8080

using namespace std;

int main(int argc, char* argv[]) {
    HttpServer server(PORT);
    server.run();
    return 0;
}
