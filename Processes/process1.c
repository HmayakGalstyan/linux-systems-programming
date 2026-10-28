#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void factorial(int num);
void logarithm(int num);
void cube(int num);

int main() {
    int num;
    scanf("%d", &num);

    pid_t childPid1 = fork();
    if (childPid1 == -1) {
        perror("error\n");
        exit(1);
    } else if (childPid1 == 0) {
        kill(getpid(), SIGSTOP);
        logarithm(num);
        
        printf("%d\n", getpid());
        exit(0);
    } else {
        printf("Parrent process\n");
    }

    pid_t childPid2 = fork();
    if (childPid2 == -1) {
        perror("error\n");
        exit(1);
    } else if (childPid2 == 0) {
        kill(getpid(), SIGSTOP);
        factorial(num);

        printf("%d\n", getpid());
        exit(0);
    } else {
        printf("Parrent process\n");
    }

    pid_t childPid3 = fork();
    if (childPid3 == -1) {
        perror("error\n");
        exit(1);
    } else if (childPid3 == 0) {
        kill(getpid(), SIGSTOP);
        cube(num);
        printf("%d\n", getpid());
        exit(0);
    } else {
        printf("Parrent process\n");
    }

    int result1 = setpgid(childPid1, 0);
    int result2 = setpgid(childPid2, childPid1);
    int result3 = setpgid(childPid3, childPid1);

    if (result1 == -1 || result2 == -1 || result3 == -1) {
        perror("setpgid\n");
        exit(1);
    }
    
    int status;
    waitpid(childPid1, &status, WUNTRACED);
    int stopped1 = WIFSTOPPED(status);

    waitpid(childPid2, &status, WUNTRACED);
    int stopped2 = WIFSTOPPED(status);

    waitpid(childPid3, &status, WUNTRACED);
    int stopped3 = WIFSTOPPED(status);
   
    if (stopped1 && stopped2 && stopped3) {
        killpg(childPid1, SIGCONT);
    }

    pid_t finishedPid = wait(&status);

    if (finishedPid == childPid1) {
        kill(childPid2, SIGKILL);
        kill(childPid3, SIGKILL);
    } else if (finishedPid == childPid2) {
        kill(childPid1, SIGKILL);
        kill(childPid3, SIGKILL);
    } else {
        kill(childPid1, SIGKILL);
        kill(childPid2, SIGKILL);
    }
    
    

    return 0;
}

void factorial(int num) {
    int result = 1;
    
    for (int i = 2; i <= num; i++) {
        result *= i;
    }

    printf("factorial = %d\n", result);

}

void logarithm(int num) {
    double log = num;

    int i = 0;
    while (log > 1) {
        log /= 2;
        i++;
    }

    printf("log = %lf\n", log);
}

void cube(int num) {
    int x = 1;
    for (int i = 0; i < 3; i++) {
        x *= num;
    }

    printf("cube = %d\n", x);
}