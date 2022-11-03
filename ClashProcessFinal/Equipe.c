#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

void reveil(int sig);
// void pidpereW(void);//ecrit le pid du pere dans un fichier

int main(int argc, char *argv[])
{
    char *argz[3]; // car il faut passer le nb de fichier en arguments
    argz[0] = "F";
    argz[1] = argv[1];
    argz[2] = NULL;
    int pid, pid1, pid2, pid3, pid4; // On crée toutes les variables pour stocker les pids des fils

    signal(SIGUSR1, reveil); // configuration du signal SIGUSR1 avec la fonction reveil
                             // pidpereW();

    pid = fork(); // création du premier fils

    if (pid == 0) // partie fils
    {
        execv("F", argz); // le fils execute le programme deja compilé qui à un binaire qui se nomme F
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
            pause();       // le pere attend le signal de son fils pour en créer un autre
            pid2 = fork(); // création du second fils
            if (pid2 == 0)
            {
                execv("F", argz);
            }
            else
            {
                pause();       // le pere attend le signal de son fils pour en créer un autre
                pid3 = fork(); // création du troisieme fils
                if (pid3 == 0)
                {
                    execv("F", argz);
                }
                else
                {
                    pause();       // le pere attend le signal de son fils pour en créer un autre
                    pid4 = fork(); // création du quatrieme fils
                    if (pid4 == 0)
                    {
                        execv("F", argz);
                    }
                    else
                    {
                        pause(); // le pere attend le signal de son fils pour passer a autre chose
                        printf("\n\n Je suis avant de partir dans l'autre fichier\n\n");
                        argz[0] = "P"; // on modifie le nom du fichier pour aller dans celui du pere
                        // printf("ARGZ:%s\n", argz[1]);
                        execv("P", argz);
                        // execl("/bin/xterm", "bin/xterm", "-e", "./P", argz, NULL);
                    }
                }
            }
        }
    }
    return 0;
}

void reveil(int sig) // lorsque le fils envoie le signal c'est le pere qui execute cette partie
{
    printf("\nJe suis le pere %d \t je vais faire la suite \n", getpid());
}

// void pidpereW(void)
// {
//     int stock_fil;
//     int pidpere;
//     FILE *file;

//     file = fopen("PERE1.dat", "r+b"); // on ouvre le fichier que l'on vient de tirer au hasard
//     if (file == NULL)
//     {
//         printf(" Erreur d'ouverture du fichier \n");
//         fclose(file);
//     }
//     else
//     {
//         fread(&pidpere, sizeof(int), 1, file); // lecture du ppid stocké dans le fichier
//         if (!feof(file))
//         {
//             fclose(file);
//             file = fopen("PERE2.dat", "r+b");

//             if (file == NULL)
//             {
//                 printf(" Erreur d'ouverture du fichier \n");
//                 fclose(file);
//             }
//             else
//             {
//                 printf("Le fichier PERE2 est vide on peut écrire \n");
//                 stock_fil = getpid();
//                 fwrite(&stock_fil, sizeof(stock_fil), 1, file);
//                 fclose(file);
//             }
//         }
//         else
//         {
//             printf("Le fichier PERE1 est vide on peut écrire \n");
//             stock_fil = getpid();
//             fwrite(&stock_fil, sizeof(int), 1, file);
//             fclose(file);
//         }
//     }
// }