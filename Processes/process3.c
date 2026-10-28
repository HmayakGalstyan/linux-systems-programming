#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t childPid = fork(); 

    if (childPid == -1) {
        perror("error\n");
        exit(1);
    } else if (childPid == 0) {
        printf("Child process is running\n");
        printf("%d\n", getpid());
        printf("%d\n", getppid());
        raise(SIGSEGV);
        
    } else {
        printf("Parent process is running\n");
        printf("child process pid = %d\n", childPid);
        printf("parent process pid = %d\n", getpid());
    }

    int status;
    int endSigNum = 0;
    wait(&status);
  
    if (WIFSIGNALED(status)) {
        endSigNum = WTERMSIG(status);
    }
            
    printf("child process end signal num = %d\n", endSigNum);
    
    
    return 0;
}