#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int pid;
int pipe1[2];
int pipe2[2];

void exec1();
void exec2();
void exec3();

int main()
{

    // create pipe1
    if (pipe(pipe1) == -1)
    {
        perror("bad pipe1");
        exit(1);
    }

    if ((pid = fork()) == -1)
    {
        exit(1);
    }
    else if (pid == 0)
    {
        exec1();
    }

    if (pipe(pipe2) == -1)
    {
        perror("bad pipe2");
        exit(1);
    }

    if ((pid = fork()) == -1)
    {
        exit(1);
    }
    else if (pid == 0)
    {
        exec2();
    }

    close(pipe1[0]);
    close(pipe1[1]);

    if ((pid = fork()) == -1)
    {
        exit(1);
    }
    else if (pid == 0)
    {
        exec3();
    }
}

void exec1()
{

    // output to pipe1
    dup2(pipe1[1], 1);

    close(pipe1[0]);
    close(pipe1[1]);
    // exec
    execlp("ps", "ps", "-aux", NULL);
    _exit(1);
}

void exec2()
{
    // input from pipe1
    dup2(pipe1[0], 0);
    // output to pipe2
    dup2(pipe2[1], 1);

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    execlp("sort", "sort", "-nrk", "3,3", NULL);
    _exit(1);
}

void exec3()
{
    // input from pipe2
    dup2(pipe2[0], 0);

    close(pipe2[0]);
    close(pipe2[1]);

    execlp("head", "head", "-5", NULL);

    _exit(1);
}
