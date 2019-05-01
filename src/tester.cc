#include "request.h"
#include "server.h"

char* htmlPage = 
    "<h1>Welcome to </h1><h1 style='color: red'>Racquet</h1>"; // I am going to serve this HTML to microsoft edge

char* home(Request request) {
    return htmlPage;
}


char* index(Request request) {
    return "Welcome to Racquet!";
}


int main() {
    Server server = Server((char*) "3490");

    server.assignStaticPath("/home", REQUEST_GET, home);
    server.assignStaticPath("/", REQUEST_GET, index);

    server.start();
}