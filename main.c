#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "str.h"

int main() {
    char *test = "NIGGER BOUB SHIT";
    String n = NewString(test);
    if(n.Is(&n, "NIGGER BOUB SHIT"))
        printf("Match!\n");

    if(n.Contains(&n, "NIGGER"))
        printf("Contains!\n");

    if(n.StartsWith(&n, "NIGGER"))
        printf("StartsWith!\n");

    if(n.EndsWith(&n, "SHIT"))
        printf("EndsWith!\n");

    return 0;
}