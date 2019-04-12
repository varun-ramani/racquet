#ifndef REQUEST_H
#define REQUEST_H

// Common request method types
#define REQUEST_GET 0
#define REQUEST_POST 1
#define REQUEST_HEAD 2
#define REQUEST_PUT 3
#define REQUEST_DELETE 4
#define REQUEST_CONNECT 5
#define REQUEST_OPTIONS 6
#define REQUEST_TRACE 7

class Request {

public:
    Request(char* request_text);
    ~Request();
    int get_method();
    char* get_body();
    char* get_uri();

private:
    char body[10000];
    char uri[300];
    int method;
};

#endif
