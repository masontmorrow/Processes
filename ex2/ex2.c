// Write a program that opens the text.txt  file (with the `fopen()` system call) located in this directory 
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor 
// returned by `fopen()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    FILE* txt_file = fopen("text.txt", "r");
    if(!txt_file) {
        perror("Failure opening file.");
        return EXIT_FAILURE;
    }

    printf("hello world (pid: %d)\n", (int)getpid());
    int rc = fork();

    if (rc < 0)
    { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child process satisfies this branch
        printf("hello, child here (pid: %d) \n", (int)getpid());
    }
    else
    {
        printf("hello, parent here (pid: %d) of child %d\n", (int)getpid(), rc);
    }

    int c;
    while ((c = fgetc(txt_file)) != EOF)
    {
        putchar(c);
    }

    if (ferror(txt_file))
    {
        printf("error reading file in (pid: %d)\n", (int)getpid());
    }
    else if (feof(txt_file))
    {
        printf("end of file reached in (pid: %d\n", (int)getpid());
    }

    return 0;
}
