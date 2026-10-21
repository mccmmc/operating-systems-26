#include <stdio.h>
#include <unistd.h>

int main() {
    setbuf(stdout, NULL);
    while (1) {
        printf("Hello world!\n");
        sleep(1);
    }
    return 0;
}
