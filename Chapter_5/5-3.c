/*   
 *  The Linux Programming Interface
 *  Exercise 5.3
 *  Bmo 
 */
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

/* Create Buffer for I/O  */
#define BUFFER 1024

/* Global Variables  */
int xflag = 0;  
int warnflag = 0;

/* Error checking function */
void errCheck(char *errorIn)
{
    puts(errorIn);
    exit(EXIT_FAILURE);
}

/* Use getopt to parse arguments */
void checkArgs(int argc, char **argv)
{
    int opt;
    while ((opt = getopt (argc, argv, "x")) != -1)
        switch(opt)
        {
            case 'x':
                xflag = 1;
                break;
            case '?':
                warnflag = 1;
                break;
            default:
                abort ();
        }
}

int main(int argc, char **argv)
{
    if (argc < 3 || strcmp(argv[1], "--help") == 0) 
        errCheck("Usage: ./5-3 <file> numbytes [x]");

    int i, numBytes, inputFile, filePerms, openFlags;
    off_t offset;
    char buf[BUFFER];
    ssize_t numRead;

    numBytes = argv[2];

    /* rw-rw-rw- or 0666 before the umask is applied */
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    if (inputFile = open(argv[1], openFlags, filePerms) == -1)
        errCheck("Error, failed to open file");


    if (xflag == 1) {
        /* Do not open the file with O_APPEND so we can show what happens when we don't write to a file atomically */
        openFlags = O_WRONLY | O_CREAT;

        for (i = 0; i < numBytes; i++)
        {        
            /* Seek to the end of the file */
            if (offset = lseek(inputFile, 0, SEEK_END) == (off_t) -1)
                errCheck("Error seeing to the value specified as numbytes"); 
        
            if (write(inputFile, "x", 1) != 1) 
                errCheck("Write using lseek failed");
        }

    } 
    else if (warnflag == 1) {
        printf("Unknown option %-c\n", optopt);
        exit(EXIT_FAILURE);
    }
    else {
        openFlags = O_WRONLY | O_CREAT | O_APPEND;
    }

    exit(EXIT_SUCCESS);
}
