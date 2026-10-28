#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int num);
void signalSet();

int main() {
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    signalSet();

    return 0;
}

void handler(int num) {
    switch (num) {
    case SIGINT:
        write(1, "SIGINT\n", 8);
        break;
    case SIGTSTP:
        write(1, "SIGTSTP\n", 8);
        break;
    default:
        break;
    }
    
}

void signalSet() {
    raise(SIGINT);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTSTP);

    sigprocmask(SIG_BLOCK, &mask, NULL);
    write(1, "BLOCK\n", 6);

    for (int i = 0; i < 3; i++) {
      raise(SIGINT);
    }

    raise(SIGTSTP);
    sigset_t pending;
    sigpending(&pending);

    if (sigismember(&pending, SIGINT) != 0 && 
        sigismember(&pending, SIGTSTP) != 0) {
        write(1, "UNBLOCK\n", 8);
    }

    sigprocmask(SIG_UNBLOCK, &mask, NULL);
}