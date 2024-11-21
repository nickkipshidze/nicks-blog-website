#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "views.h"
#include "strutils.h"

char *viewRoot(char *request, size_t *reslen) {
    const char HTTPBody[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";

    char *indexHTMLContent = NULL;
    readFile("./static/index.html",  &indexHTMLContent);

    *reslen = strlen(HTTPBody) + strlen(indexHTMLContent) + 1;
    char *response = (char *) malloc(*reslen);
    response[0] = '\0';

    strcat(response, HTTPBody);
    strcat(response, indexHTMLContent);

    free(indexHTMLContent);
    return response;
}

char *viewNotFound(char *request, size_t *reslen) {
    const char HTTPBody[] = "HTTP/1.1 404 NOT FOUND\nContent-Type: text/html\n\n";

    char *notfoundHTMLContent = NULL;
    readFile("./static/404.html",  &notfoundHTMLContent);

    *reslen = strlen(HTTPBody) + strlen(notfoundHTMLContent) + 1;
    char *response = (char *) malloc(*reslen);
    response[0] = '\0';

    strcat(response, HTTPBody);
    strcat(response, notfoundHTMLContent);

    free(notfoundHTMLContent);
    return response;
}

char *viewFavicon(char *request, size_t *reslen) {
    const char HTTPBody[] = "HTTP/1.1 200 OK\nContent-Type: image/vnd.microsoft.icon\n\n";

    char *faviconICOContent = NULL;
    long faviconSize = readBinFile("./static/favicon.ico", &faviconICOContent);

    *reslen = strlen(HTTPBody) + faviconSize;
    char *response = (char *) malloc(*reslen + 1);
    response[0] = '\0';

    strcpy(response, HTTPBody);
    memcpy(response + strlen(HTTPBody), faviconICOContent, faviconSize);
    free(faviconICOContent);

    return response;
}

char *viewStyleCSS(char *request, size_t *reslen) {
    const char HTTPBody[] = "HTTP/1.1 200 OK\nContent-Type: text/css\n\n";

    char *styleCSSContent = NULL;
    readFile("./static/style.css", &styleCSSContent);

    *reslen = strlen(HTTPBody) + strlen(styleCSSContent) + 1;
    char *response = (char *) malloc(*reslen + 1);
    response[0] = '\0';

    strcat(response, HTTPBody);
    strcat(response, styleCSSContent);

    free(styleCSSContent);
    return response;
}

char *routeRequest(char *request, size_t *reslen) {
    char *requestLine = getRequestLine(request);
    char *method = getReqLineMethod(requestLine);
    char *path = getReqLinePath(requestLine);

    printf("[+] Request - %s - %s\n", method, path);

    char *response = NULL;

    if (strcmp(method, "GET") == 0) {
        if (strcmp(path, "/") == 0)
            response = viewRoot(request, reslen);
        if (strcmp(path, "/favicon.ico") == 0)
            response = viewFavicon(request, reslen);
        if (strcmp(path, "/style.css") == 0)
            response = viewStyleCSS(request, reslen);
    }

    if ((int)*reslen == -1 || response == NULL){
        response = viewNotFound(request, reslen);
    }

    free(requestLine);
    free(method);
    free(path);

    return response;
}
