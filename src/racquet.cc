#include "request.h"
#include "server.h"

char *index(Request request) {
    printf("Hit index!\n");
    return (char*)"";
    //return request.get_body();
}

char *home(Request request) {
    printf("Welcome home!\n");
    return (char*)"";
}


int main(int argc, char *argv[]) {

    Server server = Server((char*)"3490");
    server.assignStaticPath(std::string("/"), REQUEST_GET, index);
    server.assignStaticPath(std::string("/home"), REQUEST_GET, home);
    server.start();

    return 0;
}
