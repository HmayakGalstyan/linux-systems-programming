#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

void handler(int num);

pid_t childPid;

int main() {
    childPid = fork();
    if (childPid == -1) {
        perror("error\n");
        exit(1);
    } else if (childPid == 0) {
        sleep(5);
        exit(0);
    } else {
        signal(SIGALRM, handler);
        alarm(7);

        int status;
        pid_t finishedPid = waitpid(childPid, &status, 0);

        if (finishedPid == childPid) {
           if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
              alarm(0);
              printf("[WATCHDOG] Child finished successfully\n");
           }
        } else {
            printf("!finishedPid != childPid");
        }
    }

    return 0;
}

void handler(int num) {
    switch (num) {
    case SIGKILL:
        if (kill(childPid, SIGKILL) == 0) {
            char str[] = "[WATCHDOG] Child timed out and killed!\n";
            int size = sizeof(str) - 1;
            write(STDOUT_FILENO, str, size);
        } else {
            write(STDOUT_FILENO, "No killed\n", 10);
        } 
        break;
    
    default:
        break;
    }

    
}