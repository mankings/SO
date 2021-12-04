#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // to use tolower()
#include <string.h>

#define MAX_SIZE 20

int main() {
    char *order = getenv("SORTORDER");
    if(strcmp(order, "NORMAL") == 0 || strcmp(order, "REVERSE") == 0) {
        printf("Sort Order = %s\n", order);
    } else if(order == NULL) {
        printf("ERROR: SORTORDER not defined\n");
        return EXIT_FAILURE;
    } else {
        printf("ERROR: invalid SORTORDER value (need NORMAL or REVERSE)");
        return EXIT_FAILURE;
    }

    int n = 1, i, j;

    char **words = (char **) malloc(sizeof(char *));
    do {
        words = (char **) realloc(words, n*sizeof(char **));
        words[n-1] = (char *) malloc(MAX_SIZE);
        scanf(words[n-1], MAX_SIZE, stdin);
        printf("%s\n", words[n-1]);
    } while(isalpha(words[n-1]));
    puts("lol");
    for(i = 0; i < n; i++) {
        for(j = 0; j < strlen(words[i]); j++) {
            words[i][j] = tolower(words[i][j]);
        }
    }

    char temp[MAX_SIZE];
    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            if(strcmp(words[i], words[j]) > 0) {
                strcpy(temp, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], temp);
                }
        }
    }

    printf("\nSorted strings:\n");
    if(strcmp(order, "NORMAL") == 0) {
        for(i = 0; i < n; i++) {
            puts(words[i]);
        }
    } else {
        for(i = n-1; i >= 0; i--) {
            puts(words[i]);
        }
    }

    return EXIT_SUCCESS;
}