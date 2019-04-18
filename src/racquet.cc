#include "request.h"
#include "server.h"

char *goon(Request request) {
    printf("goon\n");
    return (char*)"";
    //return request.get_body();
}

int main(int argc, char *argv[]) {

    Server server = Server((char*)"3490");
    // server.assignFunction((char*)"/index", REQUEST_GET, goon);
    server.start();


    return 0;
}
