#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = {"ps", "-e", "-f", NULL};
    execv("/bin/ps", args);

    return 0;
}
