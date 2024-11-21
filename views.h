#ifndef VIEWS_H
#define VIEWS_H

#include <stdlib.h>

char *routeRequest(char *request, size_t *reslen);

char *viewRoot(char *reques, size_t *reslent);

char *viewNotFound(char *request, size_t *reslen);

char *viewFavicon(char *request, size_t *reslen);

char *viewStyleCSS(char *request, size_t *reslen);

#endif
