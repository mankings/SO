#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
    if(argc != 4) {
        printf("Erro: número de argumentos errado (%d).\nExpected: 3.\n", argc-1);
        return EXIT_FAILURE;
    }
    
    char* ptr;
    float a = strtod(argv[1], &ptr);
    float b = strtod(argv[3], &ptr);
    char op = *argv[2];
    float x = 0;
    switch(op) {
        case '+':
            x = a + b;
            break;
        case '-':
            x = a - b;
            break;
        case '*':
            x = a * b;
            break;
        case '/':
            x = a / b;
            break;
        case 'p':
            x = pow(a, b);
            break;
        default:
            printf("Operação inválida!\n");
            return EXIT_FAILURE;
    }
    printf("%.1f %c %.1f = %.1f\n", a, op, b, x);
}