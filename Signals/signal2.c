#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void toBinary(int num);
void handler(int num);

int main() {
  signal(SIGUSR1, handler);
  signal(SIGUSR2, handler);

  int x;
  scanf("%d", &x);
  toBinary(x);
  return 0;
}

void toBinary(int num) {
   if (num == 0) {
     kill(getpid(), SIGUSR2);
     return; 
   }

   int temp = 1;
   while (temp * 2 <= num) {
     temp = temp * 2;
   }

   while (temp != 0) {
     if ((num & temp) != 0) {
        kill(getpid(), SIGUSR1);
     } else {
        kill(getpid(), SIGUSR2);
     }

    temp >>= 1;
   }
   

}

void handler(int num) {
   switch (num) {

   case SIGUSR1:
    write(STDOUT_FILENO, "1", 1);
    break;

   case SIGUSR2:
    write(STDOUT_FILENO, "0", 1);
    break;
   }

}