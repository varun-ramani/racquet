#include "request.h"
#include "server.h"

int main(int argc, char *argv[]) {

    Server server = Server((char*)"3490");
    int newsocketfd = server.start();
    
    char buffer[10000];

    recv(newsocketfd, buffer, 10000, 0);
    // printf("%s", buffer);

    Request request = Request(buffer);
    printf("Method: %d\n", request.getmethod());
    printf("URI: %s\n", request.geturi());

    send(newsocketfd, "Henlo world", strlen("Henlo world"), 0);

    close(newsocketfd);

    return 0;
}
