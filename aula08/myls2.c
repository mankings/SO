#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("===============================\n");
    switch (fork()) {
    case -1:
        perror("Erro no fork\n");
        return EXIT_FAILURE;
    case 0:
        if (execl("../aula07/myls", "../aula07/myls", "-d", "..", NULL) < 0) {
            perror("Erro no acesso ao ficheiro myls");
            return EXIT_FAILURE;
        }
        break;
    default:
        if (wait(NULL) < 0) {
            perror("Erro na espera da terminação do processo filho");
            return EXIT_FAILURE;
        }
        printf("===============================\n");
    }

    return EXIT_SUCCESS;
}