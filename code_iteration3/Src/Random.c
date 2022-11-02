#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int alea(int nbfic);
void verif(int nbmax);

int main(void)
{
    srand(time(NULL));
    int max;
    printf("\nEntrer le nombre max du alea\n");
    scanf("%d", &max);
    printf("\nLe nom de votre fichier est : %d \n", alea(max));

    verif(max);

    return 0;
}

int alea(int nbfic)
{
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
        printf("\nLe nom de votre fichier est : %d \n", randomnb);
        sleep(1);
    }
    printf("\npas bon !!!!\n");
}