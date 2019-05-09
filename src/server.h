/*
    Copyright (c) Varun Ramani. All rights reserved
*/

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

typedef char* (*static_route_action)(Request);
typedef char* (*dynamic_route_action)(Request, char *array[]);

class Server {

public:
    Server(char* port);
    ~Server();
    int getsocketfd();
    void start();
    static_route_action retriveStaticAction(std::string route, int method);
    dynamic_route_action retriveDynamicAction(std::string route, int method);
    void assignStaticPath(std::string route, int method, static_route_action action);
    void assignDynamicPath(std::string route, int method, dynamic_route_action action);

private:
    int socketfd;
    char port[10];
    std::unordered_map<std::string, std::unordered_map<int, static_route_action>*> staticActions;
    std::unordered_map<std::string, std::unordered_map<int, dynamic_route_action>*> dynamicActions;
};

#endif
