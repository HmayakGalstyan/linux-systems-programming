#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

void handler(int num);

int main() {
    pid_t childPid = fork();

    if (childPid == -1) {
        perror("error\n");
        exit(1);
    } else if (childPid == 0) {
        signal(SIGUSR1, handler);
        while (1) {
          pause();
        }

    } else {
        sleep(1);
        kill(childPid, SIGUSR1);
        sleep(1);
        kill(childPid, SIGTERM);
        int status;
        pid_t finishedPid = waitpid(childPid, &status, 0);
        if (WIFSIGNALED(status)) {
            int sigNum = WTERMSIG(status);
            printf("[PARENT] Child was killed by signal: %d\n", sigNum);
        }
        

    }



    return 0;
}

void handler(int num) {
    switch (num) {
    case SIGUSR1:
        char str[] = "[CHILD] Received SIGUSR1 signal!\n";
        int size = sizeof(str) - 1;
        write(STDOUT_FILENO, str, size);
        break;
    
    default:
        break;
    }

}