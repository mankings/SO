#include <stdio.h>
#include <stdlib.h>

#define LINEMAXSIZE 20 /* or other suitable maximum line size */

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man qsort
*/

int compareInts(const void *px1, const void *px2) {
    int x1 = *((int *)px1);
    int x2 = *((int *)px2);
    return(x1 < x2 ? -1 : x1 == x2 ? 0 : 1);
}

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    char line [LINEMAXSIZE];

    int i, numSize = 0;
    int *numbers;

    if( argc == 1 ) {
        printf("USAGE: %s fileName ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r");
    if( fp == NULL ) {
        perror ("Error opening file");
        return EXIT_FAILURE;
    }

    numbers = (int *) malloc(sizeof(int) * numSize);
    while(fgets(line, sizeof(line), fp) != NULL ) {
            numbers = (int *) realloc(numbers, sizeof(int) * ++numSize);
            numbers[numSize-1] = atoi(line);
            
    }
    fclose(fp);

    /* void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)); 
         The qsort() function sorts an array with nmemb elements of size size.*/
    qsort(numbers, numSize, sizeof(int), compareInts);

    /* Printing the sorted numbers */
    printf("Sorted numbers: \n");
    for(i = 0 ; i < numSize ; i++) {
        printf("%d\n", numbers[i]);
    }

    return EXIT_SUCCESS;
}
