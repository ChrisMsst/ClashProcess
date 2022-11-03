#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int alea(int nbfic);
void verif(int nbmax);

int main(void)
{
    int max = 10;
    printf("\nProgramme %d : Le nom de votre fichier est : %d \n",getpid(), alea(max));

    verif(max);

    return 0;
}

int alea(int nbfic)
{
    srand(time(NULL));
    int aleanum;
    aleanum = rand() % nbfic + 1;
    return aleanum;
}

void verif(int nbmax)
{
    int randomnb;
    while (randomnb <= nbmax)
    {
        randomnb = alea(nbmax);
        printf("\nProgramme %d :Le nom de votre fichier est : %d \n",getpid(), randomnb);
        sleep(1);
    }
    printf("\nProgramme %d :pas bon !!!!\n",getpid());
}