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
                continue;
            case C_ARRAY_APPEND:
                String__AppendArray(s, ((const char **)((void **)arr[i])[1]));
                continue;
            case INT_APPEND:
                String__AppendInt(s, ((int)((void **)arr[i])[1]));
                continue;
            case I_ARRAY_APPEND:
                String__AppendIntArray(s, ((int *)((void **)arr[i])[1]));
                continue;
        }
    }

    return 1;
}

char *CreateString(char **arr) {
    String n = NewString(NULL);

    for(int i = 0; arr[i] != NULL; i++) {
        n.AppendString(&n, arr[i]);
    }
    n.data[n.idx] = '\0';

    if(n.idx > 0) {
        char *resp = strdup(n.data);
        n.Destruct(&n);
        return resp;
    }

    n.Destruct(&n);
    return NULL;
}

char *iString(int i) {
    char *buff = (char *)malloc(10);
    sprintf(buff, "%d", i);

    buff[strlen(buff)] = '\0';
    return buff;
}

void free_many_strs(void **ptrs, int farr) {
    for(int i = 0; ptrs[i] != NULL; i++) {
        free(ptrs[i]);
        ptrs[i] = NULL;
    }

    if(farr) free(ptrs);
}