#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listDir(char dirname[], int space) {
    DIR *dp;
    struct dirent *dirent;
    int i;
    char *nextDir = malloc(strlen(dirname));

    dp = opendir(dirname);
    if (dp == NULL) {
        perror("Error opening directory");
        return;
    }

    dirent = readdir(dp);
    while (dirent != NULL) {
        if (dirent->d_name[0] != '.') { // do not list hidden dirs/file
            for (i = 0; i <= 2 * space; ++i)
                printf(" ");
            if (dirent->d_type == 4) {
                printf("d %s\n", dirent->d_name);

                strcpy(nextDir, dirname);
                strcat(nextDir, "/");
                strcat(nextDir, dirent->d_name);

                listDir(nextDir, space + 1);
            } else {
                printf("- %s\n", dirent->d_name);
            }
        }

        dirent = readdir(dp);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s base_directory\n", argv[0]);
        return EXIT_FAILURE;
    }

    listDir(argv[1], 0);

    return EXIT_SUCCESS;
}
