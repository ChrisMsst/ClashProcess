#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random(int nbfic);

int main(void)
{
    srand(time(NULL));
    int max;
    printf("\nEntrer le nombre max du random\n");
    scanf("%d",&max);
    printf("\nLe nom de votre fichier est : %d \n",random(max));

}

int random(int nbfic)
{
    return rand(nbfic);
}


void verif(int nbmax)
{
    int randomnb;
    while(randomnb <= nbmax)
    {
        randomnb = random(nbmax);
        printf("\nLe nom de votre fichier est : %d \n");
    }
    printf("\npas bon !!!!\n");
}