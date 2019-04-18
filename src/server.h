#ifndef SERVER_H
#define SERVER_H

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <unordered_map>
#include <iterator>
#include "request.h"

typedef char* (*route_action)(Request);

class Server {


public:
    Server(char* port);
    ~Server();
    int getsocketfd();
    void start();
    void assignFunction(char* route, int method, route_action action);
    void retrieveFunction(char* route, int method);

private:
    int socketfd;
    char port[10];
    std::unordered_map<char*, std::unordered_map<int, route_action>> actions;
    std::unordered_map<char*, int> actionsTest;

};

#endif
