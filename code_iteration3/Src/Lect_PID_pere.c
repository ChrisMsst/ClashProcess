#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int pidpere(void)
{
    FILE *file;
    int pidpere;

    file = fopen("PERE1.dat", "r+b");
    if (file == NULL)
    {
        printf("/!\\ fichier PERE1.dat inexistant\n");
        fclose(file);
        exit(1);
    }
    else
    {
        fread(&pidpere, sizeof(int), 1, file); // lecture du ppid stocké dans le fichier
        fclose(file);
        if (feof(file)) // le fichier est vide alors:
        {
            printf("Pere %d : Mauvais fichier\n", getpid());
        }
        else
        {
            if (pidpere == getpid()) // le ppid du pere adverse trouvé est différent du pid du père qui execute cette fonction
            {
                file = fopen("PERE2.dat", "r+b");
                if (file == NULL)
                {
                    printf("/!\\ fichier PERE2.dat inexistant\n");
                    fclose(file);
                    exit(1);
                }
                else
                {
                    fread(&pidpere, sizeof(int), 1, file); // lecture du ppid stocké dans le fichier
                    fclose(file);
                    if (pidpere == getpid()) // le ppid du pere adverse trouvé est différent du pid du père qui execute cette fonction
                        pidpere = 0;
                }
            }
        }
    }
    return (pidpere);
}

void pid_pere(void)
{
    int stock_fil;
    int pidpere;
    FILE *file;

    file = fopen("PERE1.dat", "r+b"); // on ouvre le fichier que l'on vient de tirer au hasard
    if (file == NULL)
    {
        printf(" Erreur d'ouverture du fichier \n");
        fclose(file);
    }
    else
    {
        fread(&pidpere, sizeof(int), 1, file); // lecture du ppid stocké dans le fichier
        if (!feof(file))
        {
            fclose(file);
            file = fopen("PERE2.dat", "r+b");

            if (file == NULL)
            {
                printf(" Erreur d'ouverture du fichier \n");
                fclose(file);
            }
            else
            {
                printf("Le fichier PERE2 est vide on peut écrire \n");
                stock_fil = getpid();
                fwrite(&stock_fil, sizeof(stock_fil), 1, file);
                fclose(file);
            }
        }
        else
        {
            printf("Le fichier PERE1 est vide on peut écrire \n");
            stock_fil = getpid();
            fwrite(&stock_fil, sizeof(int), 1, file);
            fclose(file);
        }
    }
}

int main(void)
{

    int pid_1;
    int pid_2;
    FILE *file;

    fonction_write();
    printf("\n\nMon PID est : %d le pid du fichier est : %d\n\n", getpid(), pidpere());

    file = fopen("PERE1.dat", "r+b"); // on ouvre le fichier que l'on vient de tirer au hasard
    if (file == NULL)
    {
        printf(" Erreur d'ouverture du fichier \n");
        fclose(file);
    }
    else
    {
        fread(&pid_1, sizeof(int), 1, file); // lecture du ppid stocké dans le fichier
        fclose(file);
    }
    file = fopen("PERE2.dat", "r+b"); // on ouvre le fichier que l'on vient de tirer au hasard
    if (file == NULL)
    {
        printf(" Erreur d'ouverture du fichier \n");
        fclose(file);
    }
    else
    {
        fread(&pid_2, sizeof(int), 1, file); // lecture du ppid stocké dans le fichier
        fclose(file);
    }

    printf("\n\nMon PID est : %d \t Fic 1 : %d \t Fic 2 : %d\n\n", getpid(), pid_2, pid_1);

    return 0;
}