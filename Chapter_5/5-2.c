/*
 *  The Linux Programming Interface
 *  Exercise 5.2
 *  Bmo
 */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
    if( argc != 2 || strcmp(argv[1], "--help") == 0)
    {
        errCheck("./5-2 <file>");
    }

    int inputFile, openFlags;
    off_t offset;
    mode_t filePerms;
    char buf[BUFFER];
    ssize_t numRead; 

    /* filePerms = rw-rw-rw- */
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    openFlags = O_WRONLY | O_CREAT | O_APPEND;

    inputFile = open(argv[1], openFlags, filePerms);
    if (inputFile == -1)
        errCheck("Error opening file input file");
    
    numRead = read(STDIN_FILENO, buf, BUFFER);

    offset = lseek(inputFile, 0, SEEK_SET);
    if (offset == (off_t) -1)
        errCheck("Error, could not seek to beginning of file");
        
    if (write(inputFile, buf, numRead) != numRead )
        errCheck("Error writing to file, am kill");

    if (close(inputFile) == -1)
        errCheck("Can't close the file, what a shit way to end this program");
 
    exit(EXIT_SUCCESS);
}
