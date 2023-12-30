#include<iostream>
#include<thread>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<bits/stdc++.h>

#include "connection.h"
#include "request.h"

// Number of bytes read from socket per request
#define MAX_REQUEST_SIZE 1024


void ConnHandler::dispatch_handler_thread(int socket) {
    std::thread handler_thread (&ConnHandler::handle, this, socket);
    handler_thread.detach();
}

void ConnHandler::handle(int socket) {
    std::string recv_message = read_msg(socket);
    std::string response = process_request(recv_message);
    send(socket, response.c_str(), strlen(response.c_str()), 0);
    close(socket);
}

std::string ConnHandler::process_request(std::string& request_string) {
    Request request;
    request.parse_string(request_string);

    printf("Received Request\n");
    printf("--------------------------\n");
    printf("Method: %i\n", request.method);
    printf("Path: %s\n", request.path.c_str());
    printf("Version: %i\n\n", request.version);

    return request_string;
}

std::string ConnHandler::read_msg(int socket) {
    std::string recv_message(MAX_REQUEST_SIZE, 0);
    read(socket, &recv_message[0], MAX_REQUEST_SIZE);
    return recv_message;
}