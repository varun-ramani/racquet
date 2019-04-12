#include "request.h"
#include <cstring>
#include <cstdio>

Request::Request(char* request_text) {
    char buffer[10000];
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
        method = GET;
    } else if (strcmp(buffer, "POST") == 0) {
        method = POST;
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

int Request::getmethod() {
    return method;
}

char* Request::getbody() {
    return body;
}

char *Request::geturi() {
    return uri;
}
