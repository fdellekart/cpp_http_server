#include<iostream>
#include<thread>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<bits/stdc++.h>

#include "connection.h"

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

std::string ConnHandler::process_request(std::string& request) {
    std::stringstream ss(request);
    std::string method;
    std::string path;
    std::string version;
    
    getline(ss, method, ' ');
    getline(ss, path, ' ');
    getline(ss, version, '\n');

    printf("Received Request\n");
    printf("--------------------------\n");
    printf("Method: %s\n", method.c_str());
    printf("Path: %s\n", path.c_str());
    printf("Version: %s\n\n", version.c_str());

    return request;
}

std::string ConnHandler::read_msg(int socket) {
    std::string recv_message(MAX_REQUEST_SIZE, 0);
    read(socket, &recv_message[0], MAX_REQUEST_SIZE);
    return recv_message;
}