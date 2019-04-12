#include "server.h"
#include "request.h"

Server::Server(char* port) {
    int status;
    strcpy(this->port, port);


    // These structures hold the server-integral
    // data
    addrinfo hints;
    addrinfo *servinfo;

    // Zero out hints
    memset(&hints, 0, sizeof hints);

    // Specify some options 
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;

    // Run getaddrinfo and make sure that it worked
    if ((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        printf("Error on getaddrinfo(): %s", gai_strerror(status));
    }

    // Create socket 
    this->socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    int yes = 1;

    // Make socket reusable
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    // This code doesn't seem to work yet 
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

    sockaddr* incoming_addr;
    socklen_t* addr_size;

    // The program hangs and waits for a connection
    int newsocketfd;
    char buffer[10000];
    while (true) {
        memset(buffer, 0, 10000);
        newsocketfd = accept(this->socketfd, incoming_addr, addr_size);

        // Read HTTP request into buffer
        // Generate Request object
        // Request object is used to parse raw request into usable data
        recv(newsocketfd, buffer, 10000, 0);
        Request incoming_request = Request(buffer);

        send(newsocketfd, "Received!", strlen("Received"), 0);
        
        close(newsocketfd);
    }
}

Server::~Server() {
    close(socketfd);
}

int Server::getsocketfd() {
    return socketfd;
}
