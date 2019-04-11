class Request {

public:
    const int GET = 0;
    const int POST = 1;

    Request(char* request_text);
    int getmethod();
    char* getbody();
    char* geturi();

private:
    char body[10000];
    char uri[300];
    int method;
};
