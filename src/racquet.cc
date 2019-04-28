#include "request.h"
#include "server.h"

char *fakemethod(Request request) {
    printf("fakemethod\n");
    return (char*)"";
    //return request.get_body();
}


int main(int argc, char *argv[]) {

    Server server = Server((char*)"3490");
    server.assignFunction("/index", REQUEST_GET, fakemethod);
    server.start();

    return 0;
}
