#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "strutils.h"

void readFile(char *filename, char **content) {
    FILE *file = fopen(filename, "r");

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    *content = malloc(fsize + 1);
    fread(*content, 1, fsize, file);

    (*content)[fsize] = '\0';
    fclose(file);
}

long readBinFile(char *filename, char **content) {
    FILE *file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    *content = (char *)malloc(fsize);
    fread(*content, 1, fsize, file);
    fclose(file);
    return fsize;
}

long getFileSize(char *filename) {
    FILE *file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);
    return fileSize;
}

char *getRequestLine(char *request) {
    const char *endOfRequestLine = strchr(request, '\n');
    size_t requestLineLength = endOfRequestLine - request;
    char *requestLine = (char *) malloc(requestLineLength + 1);
    strncpy(requestLine, request, requestLineLength);
    requestLine[requestLineLength] = '\0';
    return requestLine;
}

char *getReqLinePath(char *requestLine) {
    char *firstSpace = strchr(requestLine, ' ');
    char *secondSpace = strchr(firstSpace + 1, ' ');
    ssize_t pathLength = secondSpace - (firstSpace + 1);
    char *path = (char *) malloc(pathLength + 1);
    strncpy(path, firstSpace + 1, pathLength);
    path[pathLength] = '\0';
    return path;
}

char *getReqLineMethod(char *requestLine) {
    char *firstSpace = strchr(requestLine, ' ');
    ssize_t methodLength = firstSpace - requestLine;
    char *method = (char *) malloc(methodLength + 1);
    strncpy(method, requestLine, methodLength);
    method[methodLength] = '\0';
    return method;
}
