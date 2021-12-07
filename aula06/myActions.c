#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man system
 man date
*/

int main(int argc, char *argv[]) {
    FILE *fp = fopen("command.log","a");
    char text[1024];
    time_t t = time(NULL);
    struct tm tm;

    do {
        printf("Command: ");
        scanf("%1023[^\n]%*c", text);
        tm = *localtime(&t);
        t = time(NULL);

        /* system(const char *command) executes a command specified in command
            by calling /bin/sh -c command, and returns after the command has been
            completed.
        */
        if(strcmp(text, "end")) {
           printf("\n * Command to be executed: %s\n", text);
           printf("---------------------------------\n");
           system(text);
           fprintf(fp,"%d:%d:%d - %s\n",tm.tm_hour,tm.tm_min,tm.tm_sec,text);
           printf("---------------------------------\n");
        }
    } while(strcmp(text, "end"));

    fprintf(fp,"%d:%d:%d - end\n",tm.tm_hour,tm.tm_min,tm.tm_sec);
    fclose(fp);

    printf("-----------The End---------------\n");
    
    return EXIT_SUCCESS;
}