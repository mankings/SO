#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int randomInt(int min, int max) {
    int result = 0;
    srand(time(NULL));
    result = (rand() % (max - min) + min);
    return result; 
}

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Need 2 arguments - min and max.\n");
        return EXIT_FAILURE;
    }

    char input[10];
    int attempt, count = 0, low = atoi(argv[1]), high = atoi(argv[2]);
    printf("Range: [%d, %d]\n", low, high);
    int secret = randomInt(low, high);
    
    do {
        count++;
        printf("Enter your attempt: ");
        fgets(input, sizeof(input), stdin);
        if(isdigit(input[0])) {
            attempt = strtol(input, NULL, 10);
            if(attempt > secret) printf("%d is too high!\n", attempt);
            if(attempt < secret) printf("%d is too low!\n", attempt);
        } else {
            printf("Invalid attempt! Need an int.\n");
        }
    } while(attempt != secret);
    
    printf("Nice! The secret number was %d.\nYou made %d attempts.\n", secret, count);
    return EXIT_SUCCESS;
}