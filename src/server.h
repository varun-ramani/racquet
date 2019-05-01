#ifndef SERVER_H
#define SERVER_H

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <unordered_map>
#include <iterator>
#include "request.h"
#include <iostream>

typedef char* (*route_action)(Request);

class Server {

public:
    Server(char* port);
    ~Server();
    int getsocketfd();
    void start();
    route_action retriveStaticAction(std::string route, int method);
    void assignStaticPath(std::string route, int method, route_action action);

private:
    int socketfd;
    char port[10];
    std::unordered_map<std::string, std::unordered_map<int, route_action>*> actions;
    
};

#endif
