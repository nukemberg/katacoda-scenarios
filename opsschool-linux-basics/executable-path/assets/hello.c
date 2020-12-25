#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#define _GNU_SOURCE
#include <errno.h>

extern char *program_invocation_name;
extern char *program_invocation_short_name;

int main(int argc, char **argv) {
    printf("Hello world!\n");

    for (int i=0; i<argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    printf("Program name: %s\n", program_invocation_name);

    int i = 0;
    char *env = __environ[i];
    while(env!=NULL) {
        printf("ENV[%d]: %s\n", i, env);
        env = __environ[++i];
    }
    return 0;
}