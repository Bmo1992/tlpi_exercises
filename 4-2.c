/*   
 *  The Linux Programming Interface
 *  Exercise 4.2
 *  Bmo 
 */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

/* Create Buffer for I/O  */
#define BUFFER 1024

/* Error checking function */
void errCheck(char *errorIn)
{
    puts(errorIn);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int outputFileFlags, inputFile, outputFile;
    char buf[BUFFER];
    mode_t filePerms;
    ssize_t numRead;

    /* rw-rw-rw- */
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    outputFileFlags = O_CREAT | O_TRUNC | O_WRONLY; 

    if (argc !=3 || strcmp(argv[1], "--help") == 0)
    {
        errCheck("Usage: ./4-2 inputFile.txt outputFile.txt");
    }


    inputFile = open(argv[1], O_RDWR, filePerms);
    if (inputFile == -1)
        errCheck("Error Opening input file");  

    outputFile = open(argv[2], outputFileFlags, filePerms);
    if (outputFile == -1)
        errCheck("Error opening output file");

    while ((numRead = read(inputFile, buf, BUFFER)) > 0)
    {
        if (write(outputFile, buf, numRead) != numRead)
            errCheck("Error, write to output file");
    }

    if (close(inputFile) == -1)
        errCheck("Error, cant close input file");

    if (close(outputFile) == -1)
        errCheck("Error, can't close output file");


    exit(EXIT_SUCCESS);
}


