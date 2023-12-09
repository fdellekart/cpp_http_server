#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include "server.h"

using namespace std;

HttpServer::HttpServer(uint16_t server_port) {
    port = server_port;
    opt = 1;
}

int HttpServer::run() {
    init_address();
    init_socket();
    
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        char* hello = "Hello from server";
        string recv_message = read_msg();
        printf("%s\n", recv_message.c_str());
        send(new_socket, hello, strlen(hello), 0);

        close(new_socket);
    }
    close(server_fd);

    return 0;
}

std::string HttpServer::read_msg() {
    uint32_t msg_len = read_msg_len();
    string recv_message(msg_len, 0);
    read(new_socket, &recv_message[0], msg_len);
    return recv_message;
}

uint32_t HttpServer::read_msg_len() {
    char msg_len_buffer[4];
    read(new_socket, msg_len_buffer, 4);
    return *(uint32_t *)msg_len_buffer;
}

void HttpServer::init_address() {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    addrlen = sizeof(address);
}

void HttpServer::init_socket() {
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

}
