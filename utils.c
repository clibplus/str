#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "str.h"

int String__Utils(String *s, const void **arr) {
    if(!s || !arr)
        return 0;

    for(int i = 0; arr[i] != NULL; i++) {
        switch((STR_UTILS)((void **)arr[i])[0]) {
            case STR_APPEND:
                String__AppendString(s, ((char *)((void **)arr[i])[1]));
                break;
            case C_ARRAY_APPEND:
                String__AppendArray(s, ((const char **)((void **)arr[i])[1]));
                break;
            case INT_APPEND:
                String__AppendInt(s, ((int)((void **)arr[i])[1]));
                break;
            case I_ARRAY_APPEND:
                String__AppendIntArray(s, ((int *)((void **)arr[i])[1]));
                break;
        }
    }

    return 1;
}

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