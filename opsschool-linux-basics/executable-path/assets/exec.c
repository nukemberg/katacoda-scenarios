#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    execle("hello", "hello", NULL, (char *[]){NULL});
    perror("execve");
    exit(1);
}