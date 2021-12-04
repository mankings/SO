#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // to use tolower()
#include <string.h>

#define MAX_SIZE 20

int main(int argc, char **argv) {
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

    int n = argc-1;
    int i, j;

    char words[n][MAX_SIZE];
    for(i = 0; i < n; i++) {
        strcpy(words[i], argv[i+1]);
        printf("%s\n", words[i]);
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < strlen(words[i]); j++) {
            words[i][j] = tolower(words[i][j]);
        }
    }

    char temp[MAX_SIZE];
    if(strcmp(order, "NORMAL") == 0) {
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                if(strcmp(words[i], words[j]) > 0) {
                    strcpy(temp, words[i]);
                    strcpy(words[i], words[j]);
                    strcpy(words[j], temp);
                }
            }
        }
    }

    if(strcmp(order, "REVERSE") == 0) {
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                if(strcmp(words[i], words[j]) < 0) {
                    strcpy(temp, words[i]);
                    strcpy(words[i], words[j]);
                    strcpy(words[j], temp);
                }
            }
        }
    }

    printf("\nSorted strings:\n");
    for(i = 0; i < n; i++) {
        puts(words[i]);
    }
    return EXIT_SUCCESS;
}