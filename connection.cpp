#include<iostream>
#include<thread>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>

#include "connection.h"

void ConnHandler::dispatch_handler_thread(int socket) {
    std::thread handler_thread (&ConnHandler::handle, this, socket);
    handler_thread.detach();
}

void ConnHandler::handle(int socket) {
    std::string recv_message = read_msg(socket);
    printf("%s\n", recv_message.c_str());
    char* hello = "Hello from server";
    send(socket, hello, strlen(hello), 0);
    close(socket);
}

uint32_t ConnHandler::read_msg_len(int socket) {
    char msg_len_buffer[4];
    read(socket, msg_len_buffer, 4);
    return *(uint32_t *)msg_len_buffer;
}

std::string ConnHandler::read_msg(int socket) {
    uint32_t msg_len = read_msg_len(socket);
    std::string recv_message(msg_len, 0);
    read(socket, &recv_message[0], msg_len);
    return recv_message;
}