#include<iostream>
#include<netinet/in.h>
#include<vector>
#include<filesystem>

#include "connection.h"

namespace fs = std::filesystem;

class HttpServer {
    public:
        HttpServer(uint16_t port, std::string target_dir);
        int run();
        uint16_t port;
        std::string target_dir;

    private:
        int server_fd, new_socket, opt;
        sockaddr_in address;
        socklen_t addrlen;
        ConnHandler conn_handler;
        void init_address();
        
        // Create the socket file descriptor listen for connections
        void init_socket();

        // Files in the target directory
        std::vector<fs::path> files;
};