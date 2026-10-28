#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void process_number_signals(int number);
void signal_handler(int signo);

int main() {

    for (int i = 1; i <= 8; i++) {
        signal(i, signal_handler);
    }
    signal(SIGUSR1, signal_handler);

    int x;
    if (scanf("%d", &x) == 1) {
        process_number_signals(x);
    }

    return 0;
}

void process_number_signals(int number) {
    int temp;
    while (number > 0) {
        temp = number % 10;
        number /= 10;

        if (temp >= 1 && temp <= 8) {
            kill(getpid(), temp);
        } else if (temp == 9) {
            kill(getpid(), SIGUSR1);
        }
    }
}

void signal_handler(int signo) {
    switch (signo) {
        case 1: printf("SIGHUP (1)\n"); break;
        case 2: printf("SIGINT (2)\n"); break;
        case 3: printf("SIGQUIT (3)\n"); break;
        case 4: printf("SIGILL (4)\n"); break;
        case 5: printf("SIGTRAP (5)\n"); break;
        case 6: printf("SIGABRT (6)\n"); break;
        case 7: printf("SIGBUS (7)\n"); break;
        case 8: printf("SIGFPE (8)\n"); break;
        case SIGUSR1: printf("SIGUSR1 (9-ի փոխարեն)\n"); break;
        default: break;
    }
}
