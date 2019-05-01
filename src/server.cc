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

        char* response = (char*) "HTTP/1.1 200 OK\nDate: Sun, 28 Jul 2013 15:37:37 GMT\nServer: Racquet\nLast-Modified: Sun, 07 Jul 2013 06:13:43 GMT\nTransfer-Encoding: chunked\nConnection: Keep-Alive\nContent-Type: text/html; charset=UTF-8\n<h1>Hello</h1>";

        send(newsocketfd, response, strlen(response), 0);
        printf("Hit route %s\n", incoming_request.get_uri());

        retrieveFunction(incoming_request.get_uri(), incoming_request.get_method(), incoming_request);

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
void Server::assignStaticPath(std::string route, int method, route_action routeaction) {
    std::unordered_map<int, route_action>* routeContainer = new std::unordered_map<int, route_action>;
    if (actions.find(route) == actions.end()) {
        printf("Inserting new route\n");
        actions.insert(std::make_pair(route, routeContainer));
        printf("%s\n", actions.find(route)->first.c_str());
    }
    routeContainer->insert(std::make_pair(method, routeaction));
}

void Server::retrieveFunction(std::string route, int method, Request request) {
    // printf("%s\n", actions.find(route)->first.c_str());]
    if (actions.find(route) == actions.end()) {
        printf("Route %s not valid\n", route.c_str());
    } else {
        route_action action = actions.find(route)->second->find(method)->second;
        action(request);
    }
}
