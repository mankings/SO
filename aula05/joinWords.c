#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *result = malloc(1);
    for(int i = 1; i < argc; i++) {
        result = (char *) realloc(result, strlen(result) + strlen(argv[i]));  //no need for +1 for '\0' because result already has it allocated
        strcat(result, argv[i]);
    }
    printf("%s\n", result);
    free(result);
    return 0;
}