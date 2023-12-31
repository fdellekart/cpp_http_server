#include<iostream>
#include "server.h"
#include "connection.h"

#define PORT 8080

using namespace std;

int main(int argc, char* argv[]) {
    std::string target_dir = "./files/";
    HttpServer server(PORT, target_dir);
    server.run();
    return 0;
}
