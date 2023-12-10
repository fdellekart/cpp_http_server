#include<iostream>
#include<netinet/in.h>

#include "connection.h"

class HttpServer {
    public:
        HttpServer(uint16_t port, ConnHandler connection_handler);
        uint16_t port;
        int run();

    private:
        int server_fd, new_socket, opt;
        sockaddr_in address;
        socklen_t addrlen;
        ConnHandler conn_handler;
        void init_address();
        
        // Create the socket file descriptor listen for connections
        void init_socket();
};