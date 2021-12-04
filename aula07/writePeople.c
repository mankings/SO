#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE 64

typedef struct {
    int age;
    double height;
    char name[MAX_SIZE];
} Person;

void printPersonInfo(Person *p) {
    printf("Person: %s, %d, %f\n", p->name, p->age, p->height);
}

void cleanStdin() {
    char c;
    while((c = getchar()) != EOF && c != '\n') ;
}

int main (int argc, char *argv[]) {
    FILE *fp = NULL;
    int i;
    Person p;

    // Validate number of arguments
    if(argc != 2) {
        printf("USAGE: %s fileName\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open the file provided as argument
    errno = 0;
    fp = fopen(argv[1], "wb");
    if(fp == NULL) {
        perror ("Error opening file!");
        return EXIT_FAILURE;
    }

    printf("How many people? ");
    int n;
    scanf("%d", &n);
    cleanStdin();

    // Write n itens on a file
    for(i = 1; i <= n; i++) {    
        printf("\n");
        printf("Name: ");
        fgets(p.name, MAX_SIZE+1, stdin);
        if((strlen(p.name) > 0) && (p.name[strlen(p.name)-1] == '\n')) {
            p.name[strlen(p.name)-1] = '\0';
        } // remove trailing newline, if there
        printf("Age: ");
        scanf("%d", &p.age);
        cleanStdin();
        printf("Height: ");
        scanf("%lf", &p.height);
        cleanStdin();
        fwrite(&p, sizeof(Person), 1, fp);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
