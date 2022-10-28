#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    for (int i = 0; i < 5; i++)
    {
        printf("Je suis le pere %d il me reste %d sec \n", getpid(), i);
    }
}