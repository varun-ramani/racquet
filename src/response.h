/*
    Copyright (c) Varun Ramani. All rights reserved
*/

#include <stdio.h>

#ifndef RESPONSE_H
#define RESPONSE_H

class Response {
    public:
        Response();
        void readFileIntoBody(char* filename);
        char* generateResponseText();
        
    private: 
        char body[10000];
};

#endif