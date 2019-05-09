/*
    Copyright (c) Varun Ramani. All rights reserved
*/

#include "request.h"
#include "server.h"
#include "response.h"

char* index(Request request) {
    Response response = Response();

    // Load an HTML file into the body buffer contained within response
    response.readFileIntoBody("static/index.html");

    // Add up all the buffers and send them to the server
    return response.generateResponseText();
}

char* mainCSS(Request request) {
    printf("Method run\n");
    Response response = Response();
    response.readFileIntoBody("static/main.css");
    return response.generateResponseText();
}

char* dynamicFunction(Request request, char* variables[]) {
    printf("First variable: %s\n", variables[0]);
    return "Hello";
}

int main() {
    Server server = Server((char*) "3490");
    server.assignStaticPath("/", REQUEST_GET, index);
    server.assignDynamicPath("/goon", REQUEST_GET, dynamicFunction);
    
    server.start();
}