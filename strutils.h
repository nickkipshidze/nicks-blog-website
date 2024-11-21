#ifndef STRUTILS_H
#define STRUTILS_H

void readFile(char *filename, char **content);

long readBinFile(char *filename, char **content);

long getFileSize(char *filename);

char *getRequestLine(char *request);

char *getReqLinePath(char *requestLine);

char *getReqLineMethod(char *requestLine);

#endif
