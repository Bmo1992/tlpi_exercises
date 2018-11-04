/*
 * The Linux Programming Interface
 * Exercise 6.2
 * BMO
 * This program shows how setjmp and longjmp can be misused and create an infinite loop
 */
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

static void jumper()
{
    printf("Inside jumper():");
    
    if (setjmp(env) == 0) {
        printf("Jump in jumper is set\n");
    } else {
        printf("Jumper has jumped into itself\n");
    }
}

static void jumpee()
{
    jumper();

    printf("jumpee is jumping to the jumper\n");
    longjmp(env, 1);
    printf("finished jumping to jumper\n");
}


int main(int argc, char *argv[])
{
    jumpee();
    exit(EXIT_SUCCESS);
}
