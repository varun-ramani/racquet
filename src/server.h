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

class Server {

public:
    Server(char* port);
    ~Server();
    int getsocketfd();
    int start();

private:
    int socketfd;
    char port[10];

};

#endif
