/*   
 *  The Linux Programming Interface
 *  Exercise 4.1
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
int aflag = 0;  
int warnflag = 0;

/* Error checking function */
void errCheck(char *errorIn)
{
    puts(errorIn);
    exit(EXIT_FAILURE);
}

/* Function to utilize getopt */
void checkArgs(int argc, char **argv)
{
    int opt;
    /* GNU getopt function to parse command line options  */
    while ((opt = getopt (argc, argv, "a")) != -1)
        switch(opt)
        {
            case 'a':
                aflag = 1;
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
    int i, optDiff, filePerms, teeFlags, fileMode;
    int teeFile[argc];
    char buf[BUFFER];
    ssize_t numRead;

    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;  
    /* rw-rw-rw- */ 

    checkArgs(argc, argv);
    if (aflag == 1) {
        optDiff = argc - optind;
        /* append flags */
        teeFlags = O_WRONLY | O_CREAT | O_APPEND; 
    }
    /* Warning sent to standard error when unknown cli option is used */
    else if (warnflag == 1) {
        printf("Unknown option %-c\n", optopt);
        exit(EXIT_FAILURE);
    }
    /* Default functionality of the tee program send standard input to
       standard output and to any files passed to tee as an argument.  */
    else {
        optDiff = 1;
        /* Default Flags */
        teeFlags = O_WRONLY | O_TRUNC | O_CREAT;
    }

    /* Open the file passed to the command as an argument */
    for (i = optDiff; i < argc; i++) {
        teeFile[i] = open(argv[i], teeFlags, filePerms);
        if (teeFile[i] == -1) 
            errCheck("Error opening files");
    }
    /* Send stdin to stdout */
    while ((numRead = read(STDIN_FILENO, buf, BUFFER)) > 0) {  
        if (write(STDOUT_FILENO, buf, numRead) != numRead) 
            errCheck("Error, cant print to stdout"); 
           
        /* Send standard input to each file one at a time */ 
        for (i = optDiff; i < argc; i++) {
            if (write(teeFile[i], buf, numRead) != numRead) 
                errCheck("Error can't write to files");
        }
    }
    /* Close all file descriptors */
    for (i = optDiff; i < argc; i++) {
        if (close(teeFile[i]) == -1) 
            errCheck("Error closing files");
    }
        
    exit(EXIT_SUCCESS);
}
