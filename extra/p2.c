#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int i, opt;
    int maximum, minimum;
    int maxSet = 0, minSet = 0;

    /* b)
    printf("# args: %d\n", argc);

    for (i = 1; i < argc; i++) {
        if (atoi(argv[i]) >= 100) {
            printf("%s\n", argv[i]);
        }
    }
    */

    while ((opt = getopt(argc, argv, "n:x:")) != -1) {
        switch (opt) {
        case 'n':
            minimum = atoi(optarg);
            minSet = 1;
            break;
        case 'x':
            maximum = atoi(optarg);
            maxSet = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-x max] [-n min]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        printf("Mandatory argument(s) missing\n");
        exit(EXIT_FAILURE);
    }

    for (i = optind; i < argc; i++) {
        int number = atoi(argv[i]);
        if (minSet == 1 && maxSet == 1) {
            if (number >= minimum && number <= maximum) {
                printf("%d\n", number);
            }
        } else if (minSet == 1) {
            if (number >= minimum) {
                printf("%d\n", number);
            }
        } else if (maxSet == 1) {
            if (number >= maximum) {
                printf("%d\n", number);
            }
        } else {
            printf("%d\n", number);
        }
    }

    return EXIT_SUCCESS;
}