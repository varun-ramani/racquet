/*
    Copyright (c) Varun Ramani. All rights reserved
*/

#include "request.h"
#include <cstring>
#include <cstdio>
#include <vector>

Request::~Request() {
}

char** Request::get_uri_segments() {
    auto thisvector = std::vector<char*>();
    for (int i = 0; i < (std::end(body) - std::begin(body)); i++) {
        
    }
}

Request::Request(char* request_text) {
    char buffer[10000];
    memset(buffer, '\0' , 10000);

    int requestpos = 0;

    // Extract method
    int i = 0;
    while (request_text[requestpos] != ' ') {
        buffer[i] = request_text[requestpos];
        i++;
        requestpos++;
    }
    requestpos++;
    if (strcmp(buffer, "GET") == 0) {
        method = REQUEST_GET;
    } else if (strcmp(buffer, "POST") == 0) {
        method = REQUEST_POST;
    } else if (strcmp(buffer, "HEAD") == 0) {
        method = REQUEST_HEAD;
    } else if (strcmp(buffer, "PUT") == 0) {
        method = REQUEST_PUT;
    } else if (strcmp(buffer, "DELETE") == 0) {
        method = REQUEST_DELETE;
    } else if (strcmp(buffer, "CONNECT") == 0) {
        method = REQUEST_CONNECT;
    } else if (strcmp(buffer, "OPTIONS") == 0) {
        method = REQUEST_OPTIONS;
    } else if (strcmp(buffer, "TRACE") == 0) {
        method = REQUEST_TRACE;
    }

    // Extract route
    i = 0;
    while (request_text[requestpos] != ' ') {
        buffer[i] = request_text[requestpos];
        i++;
        requestpos++;
    }
    buffer[i] = '\0';
    strcpy(uri, buffer);
}

int Request::get_method() {
    return method;
}

char* Request::get_body() {
    return body;
}

char *Request::get_uri() {
    return uri;
}
