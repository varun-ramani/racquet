/*
    Copyright (c) Varun Ramani. All rights reserved
*/

#include "server.h"

Server::Server(char* port) {
    int status;
    strcpy(this->port, port);


    // These structures hold the server specific
    // data
    addrinfo hints;
    addrinfo *servinfo;

    // Zero out hints
    memset(&hints, 0, sizeof hints);

    // Specify some options 
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Run getaddrinfo and make sure that it worked
    if ((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        printf("Error on getaddrinfo(): %s", gai_strerror(status));
    }
    
    // Create socket 
    this->socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    int yes = 1;

    // Make socket reusable
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    setsockopt(socketfd, IPPROTO_IP, TCP_NODELAY, &yes, sizeof yes);

    // Bind to socket and start listening
    // This code doesn't actually start the server
    // though
    bind(socketfd, servinfo->ai_addr, servinfo->ai_addrlen);
    listen(socketfd, 10);
}

// This is what actually starts the server
void Server::start() {
    printf("Accepting on :%s\n", this->port);

    sockaddr incoming_addr;
    socklen_t addr_size;

    // The program hangs and waits for a connection
    int newsocketfd;
    char buffer[10000];
    while (true) {
        memset(buffer, 0, 10000);
        newsocketfd = accept(this->socketfd, &incoming_addr, &addr_size);

        // Read HTTP request into buffer
        // Generate Request object
        // Request object is used to parse raw request into usable data
        recv(newsocketfd, buffer, 10000, 0);
        printf("Buffer: %s\n", buffer);
        Request incoming_request = Request(buffer);

        static_route_action action_static;
        dynamic_route_action action_dynamic;

        char* response;
        if ((action_static = retriveStaticAction(incoming_request.get_uri(), incoming_request.get_method())) != NULL) {
            response = action_static(incoming_request);
        } else {
            response = "INVALID URL";
        }

        send(newsocketfd, response, strlen(response), 0);
        printf("Hit route %s\n", incoming_request.get_uri());


        close(newsocketfd);
    }
}

Server::~Server() {
    close(socketfd);
}

int Server::getsocketfd() {
    return socketfd;
}

// Allows developer to assign routes and methods to functions
void Server::assignStaticPath(std::string route, int method, static_route_action routeaction) {
    auto routeContainer = new std::unordered_map<int, static_route_action>;
    if (staticActions.find(route) == staticActions.end()) {
        printf("Inserting new route\n");
        staticActions.insert(std::make_pair(route, routeContainer));
        printf("%s\n", staticActions.find(route)->first.c_str());
    }
    routeContainer->insert(std::make_pair(method, routeaction));
    printf("Reached end of static assignment\n");
}

void Server::assignDynamicPath(std::string route, int method, dynamic_route_action routeaction) {
    auto routeContainer = new std::unordered_map<int, dynamic_route_action>;
    if (dynamicActions.find(route) == dynamicActions.end()) {
        printf("Inserting new route\n");
        dynamicActions.insert(std::make_pair(route, routeContainer));
        printf("%s\n", dynamicActions.find(route)->first.c_str());
    }
    routeContainer->insert(std::make_pair(method, routeaction));
    printf("Reached end of dynamic assignment\n");
}

static_route_action Server::retriveStaticAction(std::string route, int method) {
    // printf("%s\n", staticActions.find(route)->first.c_str());]
    if (staticActions.find(route) == staticActions.end()) {
        printf("Route %s not valid\n", route.c_str());
        return NULL;
    } else {
        static_route_action action = staticActions.find(route)->second->find(method)->second;
        return action;
    }
}

dynamic_route_action Server::retriveDynamicAction(std::string route, int method) {
    for (auto &pair : dynamicActions) {
        printf("Iterating\n");
        printf("Comparing %s with %s\n", route.c_str(), pair.first.c_str());
        auto mismatchRef = std::mismatch(route.begin(), route.end(), pair.first.begin());
        if (mismatchRef.first == route.end()) {
            printf("We have taken the L\n");
            return NULL;
        } else {
            return pair.second->find(method)->second;
        }
    }
}
