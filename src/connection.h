#pragma once
#include<thread>

#include<request_handler.h>

class ConnHandler {
    public:
        ConnHandler();
        ConnHandler(RequestHandler request_handler);
        void dispatch_handler_thread(int socket);
    private:
        // Read four bytes for the message length and cast to uint32_t
        uint32_t read_msg_len(int socket);
        // Read a message from client
        std::string read_msg(int socket);
        void handle(int socket);
        RequestHandler reqhandler;
};