/*
 *  The Linux Programming Interface
 *  Exercise 5.2
 *  Bmo
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

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
    if( argc != 3 || strcmp(argv[1] == "--help"))
    {
        printf("\nUsage of program: \n");
        errCheck("./5-2 <file> string");
    }

    int fd, openFlags, filePerms;
    char buf[BUFFER];
    ssize_t numRead = strlen(argv[3]); 
 

    /* filePerms = rw-rw-rw- */
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    openFlags = O_WRONLY | O_CREAT | O_APPEND;

    if((fd = open(argv[1], openFlags, filePerms)) == -1)
        errCheck("Error opening file input file");
    
    if(lseek(fd, 0, SEEK_SET) == -1) 
        errCheck("Error, could not seek to beginning of file");
    
    if(write(fd, buf, numRead) != numRead )
        errCheck("Error writing to file, am kill");
    
    if(close(fd) == -1)
        errCheck("Can't close the file, what a shit way to end this program");
 
    exit(EXIT_SUCCESS);
}
