#include<iostream>
#include<bits/stdc++.h>

#include "request.h"

void Request::parse_string(std::string request) {
    std::stringstream ss(request);

    std::string method;
    std::string path;
    std::string version;
    
    getline(ss, method, ' ');
    getline(ss, path, ' ');
    getline(ss, version, '\n');
    version.pop_back();

    this->path = path;

    if (method == "GET") {
        this->method = GET;
    } else {
        perror("Unsupported method");
    }

    if (version == "HTTP/1.1") {
        this->version = HTTP1_1;
    } else {
        printf("Unsupported version: '%s'\n", version.c_str());
    }
}