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
    int stat, alive = 5;
    for (int i = 0; i < 5; i++)
    {
        printf("Je suis le pere %d il me reste %d sec \n", getpid(), i);
    }
    printf("\nIl reste %d vie\n", alive); // affiche le nombre de fils qu'il reste en vies
    wait(&stat);                          // on attend le signal de mort d'un des fils
    alive--;                              // decrémante le nombre de fils en vie
    printf("\nIl reste %d vie\n", alive); // affiche le nombre de fils qu'il reste en vies
    wait(&stat);                          // on attend le signal de mort d'un des fils
    alive--;                              // decrémante le nombre de fils en vie
    printf("\nIl reste %d vie\n", alive); // affiche le nombre de fils qu'il reste en vies
    wait(&stat);                          // on attend le signal de mort d'un des fils
    alive--;                              // decrémante le nombre de fils en vie
    printf("\nIl reste %d vie\n", alive); // affiche le nombre de fils qu'il reste en vies
    wait(&stat);                          // on attend le signal de mort d'un des fils
    alive--;                              // decrémante le nombre de fils en vie
    printf("\nIl reste %d vie\n", alive); // affiche le nombre de fils qu'il reste en vies
    wait(&stat);                          // on attend le signal de mort d'un des fils
    alive--;                              // decrémante le nombre de fils en vie
    printf("\nIl reste %d vie\n", alive); // affiche le nombre de fils qu'il reste en vies
    if (alive == 0)
        printf("\nTous les fils sont morts !!!!!\n");
    else
        printf("\nDes fils sont encore en vie !!!!!\n");
}