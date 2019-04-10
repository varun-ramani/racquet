#include <cstddef>
#include <cstdio>
#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int status;
    addrinfo hints;
    addrinfo *servinfo;

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
        printf("Ayo there was an error %s", gai_strerror(status));
    }

    int socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    int yes = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    sockaddr *incoming_addr;
    socklen_t *addr_size;

    bind(socketfd, servinfo->ai_addr, servinfo->ai_addrlen);
    listen(socketfd, 10);
    int newsocketfd = accept(socketfd, incoming_addr, addr_size);
    
    char buffer[10000];
    char quit[] = "quit";

    recv(newsocketfd, buffer, 10000, 0);
    printf("%s", buffer);



    if (strcmp(quit, buffer) == 0) {
        printf("Goodbye!\n");
    }

    char returnbuffer[20000];
    sprintf(returnbuffer, "sent %s", buffer);

    send(newsocketfd, returnbuffer, strlen(returnbuffer), 0);

    memset(buffer, '\0', 10000);


    close(newsocketfd);

    close(socketfd);

    return 0;
}
