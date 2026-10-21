#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>

void handle_sigusr1(int sig) {
    printf("\n[SIGNAL HANDLER] Caught SIGUSR1: You entered a negative number!\n");
}

void handle_sigusr2(int sig) {
    printf("\n[SIGNAL HANDLER] Caught SIGUSR2: The input is not a valid number!\n");
}

int is_number(const char *str) {
    if (str == NULL || *str == '\0') return 0;

    if (*str == '-') {
        str++;
        if (!isdigit(*str)) return 0;
    } else if (!isdigit(*str)) {
        return 0;
    }

    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int main() {
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    char input[100];

    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {

        input[strcspn(input, "\n")] = 0;


        if (!is_number(input)) {
            raise(SIGUSR2);
        }

        else if (input[0] == '-') {
            raise(SIGUSR1);
        }
        else {
            printf("Positive number: %s\n", input);
        }
    }

    return 0;
}
