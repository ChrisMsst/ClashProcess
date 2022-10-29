#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

void reveil(int sig);

int main(int argc, char *argv[])
{
    char *argz[3]; // car il faut passer le nb de fichier en arguments
    argz[0] = "F";
    argz[2] = NULL;
    int pid, stat, pid1, pid2, pid3, pid4; // On crée toutes les variables pour stocker les pids des fils

    int alive = 5;
    signal(SIGUSR1, reveil);

    pid = fork(); // création du premier fils

    if (pid == 0) // partie fils
    {
        execv("F", argz);
    }
    else // partie père
    {
        pause(); // le pere attend le signal de son fils pour en créer un autre
        pid1 = fork();
        if (pid1 == 0)
        {
            execv("F", argz);
        }
        else
        {
            pause(); // le pere attend le signal de son fils pour en créer un autre
            pid2 = fork();
            if (pid2 == 0)
            {
                execv("F", argz);
            }
            else
            {
                pause(); // le pere attend le signal de son fils pour en créer un autre
                pid3 = fork();
                if (pid3 == 0)
                {
                    execv("F", argz);
                }
                else
                {
                    pause(); // le pere attend le signal de son fils pour en créer un autre
                    pid4 = fork();
                    if (pid4 == 0)
                    {
                        execv("F", argz);
                    }
                    else
                    {
                        pause(); // le pere attend le signal de son fils pour passer a autre chose
                        printf("\n\n Je ssuis avant de partir dans l'autre fichier\n\n");
                        // strcpy(argz[0], "P");// problème avec cette ligne cela fait un core dump
                        //   execv("Pere", argz);
                    }
                }
            }
        }
        printf("\nIl reste %d vie\n", alive);
        wait(&stat);
        alive--;
        printf("\nIl reste %d vie\n", alive);
        wait(&stat);
        alive--;
        printf("\nIl reste %d vie\n", alive);
        wait(&stat);
        alive--;
        printf("\nIl reste %d vie\n", alive);
        wait(&stat);
        alive--;
        printf("\nIl reste %d vie\n", alive);
        wait(&stat);
        alive--;
        printf("\nIl reste %d vie\n", alive);
        if (alive == 0)
            printf("\nTous les fils sont morts !!!!!\n");
        else
            printf("\nDes fils sont encore en vie !!!!!\n");
        return 0;
    }
    printf("ici on est la hein ca marche");
}

void reveil(int sig) // lorsque le fils envoie le signal c'est le pere qui execute cette partie
{
    printf("\nJe suis le pere %d \t je vais faire la suite \n", getpid());
}