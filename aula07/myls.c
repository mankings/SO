#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int endsWith(const char *str, const char *suffix) {
    char *dot = strrchr(str, '.');
    if (strcmp(dot, suffix))
        return 0;
    return 1;
}

int listFiles(const char name[], const int fileType, const char *ext) {
    DIR *dp;
    struct dirent *dirent;

    dp = opendir(name);
    if (dp == NULL) {
        perror("Error opening directory");
        return EXIT_FAILURE;
    }

    dirent = readdir(dp);
    while (dirent != NULL) {
        if (dirent->d_name[0] != '.') { // do not list hidden files/directories
            if (dirent->d_type == fileType) { // print only files of the specified type
                if (ext == NULL) {
                    printf("%s\n", dirent->d_name);
                } else {
                    if (endsWith(dirent->d_name, ext) == 0) {
                        printf("%s\n", dirent->d_name);
                    }
                }
            }
        }
        dirent = readdir(dp);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    int opt, fileType, i;
    char *ext = NULL;

    while ((opt = getopt(argc, argv, "fde:")) != -1) {
        switch (opt) {
        case 'f':
            fileType = 8;
            break;
        case 'd':
            fileType = 4;
            break;
        case 'e':
            fileType = 8;
            ext = malloc(strlen(optarg));
            strcpy(ext, optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-f | -d | -e extension] dir(s)\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if(optind == argc) {
        fprintf(stderr, "Not enough arguments.\n");
        fprintf(stderr, "Usage: %s [-f | -d | -e extension] dir(s)\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (i = optind; i < argc; ++i) {
        listFiles(argv[i], fileType, ext);
    }

    return EXIT_SUCCESS;
}