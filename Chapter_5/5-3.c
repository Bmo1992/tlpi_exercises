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
    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: ./5-3 <file> numbytes [x]\n");
        exit(EXIT_FAILURE);    
    }    

    int filePerms, openFlags;
    char buf[BUFFER];
    ssize_t numRead;

    /* rw-rw-rw- or 0666 before the umask is applied */
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    if (xflag == 1) {
        /* Do not open the file with O_APPEND so we can show what happens when we don't write to a file atomically */
        openFlags = O_WRONLY | O_CREAT;
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
