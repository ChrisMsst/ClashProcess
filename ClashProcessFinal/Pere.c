#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

typedef struct ID_PID
{ // structure pour lire correctement les fichiers binaire
    int ppid;
    int pid;
} ID_PID;

// Déclaration de fonction
int fonction_read(int nbfichier); // permet de lire le pid dans un fichier
int alea(int nbfic);              // Permet de sortir une valeur aléatoire
// int pidpereL(void);               // lis le pid du pere adverse
// void reveil(int sig);

int main(int argc, char *argv[])
{
    int stat, alive = 5;
    int pidadv;
    int compteur_kill = 0;
    int compteur_max = (atoi(argv[1]) - 1) * 5;

    // signal(SIGUSR1, reveil); // configuration du signal SIGUSR1 avec la fonction reveil

    // printf("argv:%s\n", argv[1]);
    // printf("MAX= %d //////////\n", compteur_max);

    // kill(pidpereL(), SIGUSR1);
    // printf("\nPere %d : J'attends le signal de l'autre pere!!!\n", getpid());
    // pause();
    printf("\nPere %d : Patienter 10 sec\n", getpid());
    for (int i = 10; i > 0; i--)
    {
        sleep(1);
    }

    for (int i = 5; i > 0; i--)
    {

        do
        {
            pidadv = fonction_read(compteur_max * atoi(argv[1]));

            if (pidadv == 0)
            {
                printf("\nPere %d : fichier d'un fils : %d\n", getpid(), pidadv);
            }
            else
            {
                if (pidadv == 1)
                {
                    printf("\nPere %d : Le fichier est vide !!!!\n", getpid());
                }
                else
                {
                    printf("\nPere %d : Je tire sur ma cible : %d\n", getpid(), pidadv);
                    kill(pidadv, SIGKILL);
                    compteur_kill++;
                }
            }

            sleep(2);
        } while (wait(&stat) == 0);
        alive--;                                                  // decrémante le nombre de fils en vie
        printf("\nPere %d : Il reste %d vie\n", getpid(), alive); // affiche le nombre de fils qu'il reste en vies
    }
    if (alive == 0)
        printf("\nPere %d : Tous mes fils sont morts !!!!!\n", getpid());
    else
        printf("\nPere %d : Des fils sont encore en vie !!!!!\n", getpid());
}

int fonction_read(int nbfichier)
{
    char fichier[8] = ""; // chaine de caractère qui va varier en fonction du fichier que l'on veut ouvrir
    ID_PID lecturePID;
    int result = alea(nbfichier);
    FILE *file;

    snprintf(fichier, sizeof fichier, "%d.dat", result); // fonction qui permet de faire varié la chaine de caractère en fonction du result retourné par la variable aléatoire
    printf("Pere %d : lecture du fichier %d\n", getpid(), result);
    file = fopen(fichier, "r+b");
    if (file == NULL)
        printf("Pere %d : /!\\ fichier %d inexistant\n", getpid(), result);
    else
    {
        fread(&lecturePID, sizeof(ID_PID), 1, file); // lecture du ppid stocké dans le fichier
        fclose(file);
        //printf("Pere %d : !!!!!!!!! le pid du pere du fichier est : %d \t et du fils : %d !!!!!!!!!!\n", getpid(), lecturePID.ppid, lecturePID.pid);
        if (feof(file)) // le fichier est vide alors:
        {
            printf("Pere %d : Cible loupée\n", getpid());
            lecturePID.pid = 1; // retour de la fonction sera 1
        }
        else
        {
            if (lecturePID.ppid != getpid()) // le ppid du fils trouvé est différent du pid du père qui execute cette fonction
            {
                remove(fichier);
            }
            else
            {
                printf("Pere %d : Cible alliée\n", getpid());
                lecturePID.pid = 0; // sinon cela signifie que le père cible un de ses fils alors on retournera la valeur 0
            }
        }
    }
    return (lecturePID.pid);
}

int alea(int nbfic) // fonction qui tire un nombre aléatoire entre 1 et le nombre max de fichier binaire
{
    srand(time(NULL));
    int aleanum;
    aleanum = rand() % nbfic + 1;
    return aleanum;
}

// int pidpereL(void)
// {
//     FILE *file;
//     int pidpere;

//     file = fopen("PERE1.dat", "r+b");
//     if (file == NULL)
//     {
//         printf("/!\\ fichier PERE1.dat inexistant\n");
//         fclose(file);
//         exit(1);
//     }
//     else
//     {
//         fread(&pidpere, sizeof(int), 1, file); // lecture du ppid stocké dans le fichier
//         fclose(file);
//         if (feof(file)) // le fichier est vide alors:
//         {
//             printf("Pere %d : Mauvais fichier\n", getpid());
//         }
//         else
//         {
//             if (pidpere == getpid()) // le ppid du pere adverse trouvé est différent du pid du père qui execute cette fonction
//             {
//                 file = fopen("PERE2.dat", "r+b");
//                 if (file == NULL)
//                 {
//                     printf("/!\\ fichier PERE2.dat inexistant\n");
//                     fclose(file);
//                     exit(1);
//                 }
//                 else
//                 {
//                     fread(&pidpere, sizeof(int), 1, file); // lecture du ppid stocké dans le fichier
//                     fclose(file);
//                     if (pidpere == getpid()) // le ppid du pere adverse trouvé est différent du pid du père qui execute cette fonction
//                         pidpere = 0;
//                 }
//             }
//         }
//     }
//     return (pidpere);
// }

// void reveil(int sig) // lorsque le fils envoie le signal c'est le pere qui execute cette partie
// {
//     printf("\nJe suis le pere %d \t je vais faire la suite \n", getpid());
// }