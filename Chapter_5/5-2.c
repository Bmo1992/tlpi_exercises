/*
 *  The Linux Programming Interface
 *  Exercise 5.2
 *  Bmo
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Constant for memory buffer */
#define BUFFER 1024

/* Error checking function */
void errCheck(char *errorIn)
{
    puts(errorIn);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if( argc != 1 || strcmp(argv[1] == "--help"))
    {
        printf("\nUsage of program: \n");
        errCheck("./5-2 <file>");
    }

    int fd, openFlags, filePerms;
    off_t seeker;
    ssize_t numRead; 
    char buf[BUFFER];
    

    /* filePerms = rw-rw-rw- */
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    openFlags = O_WRONLY | O_CREAT | O_APPEND;

    fd = open(argv[1], openFlags, filePerms);
    if( fd == -1 )
        errCheck("Error opening file input file");

    return 0;
}
