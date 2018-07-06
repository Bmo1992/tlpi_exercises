/*
 *  The Linux Programming Interface
 *  Exercise 5.2
 *  Bmo
 */
#include <fnctl.h>
#include <unistd.h>
#include <stdio.h>

/* Constant for memory buffer */
#define BUFFER 1024

/* Error checking function */
void errCheck(char *errorIn)
{
    put(errorIn);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int fd;

    return 0;
}
