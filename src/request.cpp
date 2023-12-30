#include<iostream>
#include<bits/stdc++.h>

#include "request.h"

void Request::parse_string(std::string& request) {
    std::stringstream request_stream(request);

    std::string method;
    std::string path;
    std::string version;
    
    getline(request_stream, method, ' ');
    getline(request_stream, path, ' ');
    getline(request_stream, version, '\n');
    version.pop_back(); // Remove LF

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

    parse_headers(request_stream);
}

void Request::parse_headers(std::stringstream& request_stream) {
    std::string header;
    while (1) {
        getline(request_stream, header, '\n');
        header.pop_back();

        if (strlen(header.c_str()) == 0) {
            // Empty line separating headers from body
            break;
        }

        std::stringstream header_stream(header);
        std::string key;
        std::string value;

        getline(header_stream, key, ' ');
        getline(header_stream, value, '\n');

        key.pop_back(); // Remove colon

        headers[key] = value;
    }
}