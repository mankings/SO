#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTIMES 50

static void Interrupt(int);
unsigned int sigint_count;

int main(int argc, char *argv[]) {
    struct sigaction sigact, oldsigact;
    unsigned int i;

    /* altera a rotina de atendimento ao ^C */
    sigact.sa_handler = Interrupt;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    if (sigaction(SIGINT, &sigact, &oldsigact) < 0) {
        perror("Rotina de atendimento não instalada\n");
        return EXIT_FAILURE;
    }

    /* contador */
    printf("PID = %u\n", getpid());
    i = 0;
    while (i <= NTIMES) {
        printf("\r%08u ", i++);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");

    return EXIT_SUCCESS;
}

static void Interrupt(int signum) {
    sigint_count++;

    if (signum == SIGINT) {
        printf("\nCalma, ainda não cheguei a %d!\n", NTIMES);
        if (sigint_count == 4) {
            struct sigaction sa;
            sa.sa_flags = SA_RESETHAND;
            sa.sa_handler = SIG_DFL;
            sigaction(SIGINT, &sa, NULL);
        }
    } else {
        printf("Foi recebido um sinal diferente de SIGINT!\n");
        exit(EXIT_FAILURE);
    }
}