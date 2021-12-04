#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man fopen
 man fgets
*/

#define LINEMAXSIZE 200 /* or other suitable maximum line size */


int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    char line [LINEMAXSIZE]; 

    /* Validate number of arguments */
    if( argc == 1 ) {
        printf("USAGE: %s fileName ...\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    /* Open the file provided as argument */
    errno = 0;
    int i;
    for(i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if( fp == NULL ) {
            perror ("Error opening file!");
            return EXIT_FAILURE;
        }

        printf("File: %s\n", argv[i]);
        /* Read all the lines of the file */
        int lineCounter = 1;
        while(fgets(line, sizeof(line), fp) != NULL ) {
            printf("%2d -> %s", lineCounter, line); /* not needed to add '\n' to printf because fgets will read the '\n' that ends each line in the file */
            lineCounter++;
        }
        fclose(fp);
        puts("\n");
    }

    return EXIT_SUCCESS;
}