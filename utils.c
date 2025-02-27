#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *CreateString(char **arr) {
    char *buff = (char *)malloc(1);
    int len = 0;

    for(int i = 0; arr[i] != NULL; i++)
    {
        len += strlen(arr[i]);
        buff = realloc(buff, len + 1);
        strncat(buff, arr[i], strlen(arr[i]));
    }

    return buff;
}

char *iString(int i) {
    char *buff = (char *)malloc(10);
    sprintf(buff, "%d", i);

    buff[strlen(buff)] = '\0';
    return buff;
}