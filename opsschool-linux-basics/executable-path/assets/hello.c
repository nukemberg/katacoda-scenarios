#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    printf("Hello world!\n");

    for (int i=0; i<argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    printf("PID: %d\n", getpid());

    int i = 0;
    char *env = __environ[i];
    while(env!=NULL) {
        printf("ENV[%d]: %s\n", i, env);
        env = __environ[++i];
    }
    return 0;
}