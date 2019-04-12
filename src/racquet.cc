#include "request.h"
#include "server.h"

int main(int argc, char *argv[]) {

    Server server = Server((char*)"3942");
    server.start();
    
    return 0;
}
