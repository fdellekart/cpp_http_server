#include<iostream>
#include<netinet/in.h>

class HttpServer {
    public:
        HttpServer(uint16_t port);
        uint16_t port;
        int run();

    private:
        int server_fd, new_socket, opt;
        sockaddr_in address;
        socklen_t addrlen;
        char buffer[1024];

        void init_address();
        
        // Create the socket file descriptor listen for connections
        void init_socket();
};