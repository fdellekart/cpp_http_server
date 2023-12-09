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
        void init_address();
        
        // Create the socket file descriptor listen for connections
        void init_socket();
        // Read four bytes for the message length and cast to uint32_t
        uint32_t read_msg_len();
        // Read a message from client
        std::string read_msg();
};