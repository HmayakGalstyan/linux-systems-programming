#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig);
void reverse(int size);
void addOne(int size);
void printStateArr(int size);
void reset(int size);

int arr[5] = {1, 2, 3, 4, 5};
volatile sig_atomic_t running = 1;

int main() {
    printf("PID: %d\n", getpid());
   
    int signals[] = {SIGUSR1, SIGUSR2, SIGINT, SIGTSTP, SIGQUIT};
    for (int i = 0; i < 5; i++) {
      signal(signals[i], handler);
    }

    while (running) {
        pause();
    }
    
    return 0;
}

void handler(int sig) {
    int size = sizeof(arr) / sizeof(arr[0]);

    switch (sig) {
    case SIGUSR1:
        addOne(size);
        break;
    case SIGUSR2:
        reverse(size);
        break;
    case SIGINT:
        printStateArr(size);
        break;
    case SIGTSTP:
        reset(size);
        break;
    case SIGQUIT:
        running = 0;
        break;
    default:
        break;
    }
}

void reverse(int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
    
}

void addOne(int size) {
    for (int i = 0; i < size; i++) {
        arr[i] += 1;
    }
}

void printStateArr(int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        printf(" %d ", arr[i]);
        sum += arr[i];
    }

    printf("sum = %d \n", sum);
}

void reset(int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
}