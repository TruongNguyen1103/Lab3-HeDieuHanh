#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t child_pid = -1;

void on_sigint(int sig) {
    if (child_pid > 0) {
        kill(child_pid, SIGTERM);
        wait(NULL);
    }
    printf("\nYou are pressed CTRL+C! Goodbye!\n");
    exit(0);
}

int main() {
    printf("Welcome to IT007, I am <MSSV_CUA_BAN>!\n");

    signal(SIGINT, on_sigint);

    child_pid = fork();

    if (child_pid == 0) {
        execlp("vim", "vim", "abcd.txt", NULL);
        perror("execlp that bai");
        exit(1);
    } else {
        while (1) {
            pause();
        }
    }

    return 0;
}
