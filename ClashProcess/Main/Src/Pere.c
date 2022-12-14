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

int main(int argc, char *argv[])
{
    int stat, alive = 5;
    int pidadv;
    int compteur_kill=0;
    int compteur_max= (atoi(argv[1])-1)*5;
    printf("argv:%s\n",argv[1]);
    printf("MAX= %d //////////\n",compteur_max);
    for (int i = 0; i < 5; i++)
    {
        printf("Je suis le pere %d il me reste %d sec \n", getpid(), i);
    }

    //for (int i = 0; i < 10; i++)
    do
    {
        pidadv = fonction_read(10);

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
            sleep(2);
        }

        sleep(1);
    }while(compteur_kill!=compteur_max);
   

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

int fonction_read(int nbfichier)
{
    char fichier[8] = ""; // chaine de caractère qui va varier en fonction du fichier que l'on veut ouvrir
    ID_PID lecturePID;
    int result = alea(nbfichier);
    FILE *file;

    snprintf(fichier, sizeof fichier, "%d.dat", result); // fonction qui permet de faire varié la chaine de caractère en fonction du result retourné par la variable aléatoire
    printf("lecture du fichier %d\n", result);
    file = fopen(fichier, "r+b");
    if (file == NULL)
        printf("/!\\ fichier %d inexistant\n", result);
    else
    {
        fread(&lecturePID, sizeof(ID_PID), 1, file); // lecture du ppid stocké dans le fichier
        if (feof(file))                                  // le fichier est vide alors:
        {
            printf("Cible loupée\n");
            lecturePID.ppid = 1; // retour de la fonction sera 1
            fclose(file);
        }
        else
        {
            if (lecturePID.ppid != getpid()) // le ppid du fils trouvé est différent du pid du père qui execute cette fonction
            {
                fread(&lecturePID.pid, sizeof(ID_PID), 1, file); // alors on lit le pid stocké dans le fichier
                fclose(file);
                remove(fichier);
            }
            else
            {
                printf("Cible alliée\n");
                lecturePID.ppid = 0; // sinon cela signifie que le père cible un de ses fils alors on retournera la valeur 0
                fclose(file);
            }
        }
        
    }
    return (lecturePID.pid);
}

int alea(int nbfic) // fonction qui tire un nombre aléatoire entre 1 et le nombre max de fichier binaire
{
    int aleanum;
    aleanum = rand() % nbfic + 1;
    return aleanum;
}
