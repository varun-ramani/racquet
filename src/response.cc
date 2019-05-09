/*
    Copyright (c) Varun Ramani. All rights reserved
*/

#include "response.h"

Response::Response() {

}

void Response::readFileIntoBody(char* filename) {
    FILE* fp;
    fp = fopen(filename, "r");
    char c;
    int pos = 0;
    while ((c = getc(fp)) != EOF) {
        body[pos] = c;
        pos++;
    }
}

char* Response::generateResponseText() {
    char buffer[10100];
    sprintf(buffer, "%s", body);

    return buffer;
}