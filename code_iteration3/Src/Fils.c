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
{
	int ppid;
	int pid;
} ID_PID;

// Déclaration de fonction
int fonction_write(int max_fil, int Ppid, int Pid); // permet d'écrire le pid dans un fichier ou rien n'est écrit
int alea(int nbfic);								// Permet de sortir une valeur aléatoire

int main(int argc, char *argv[])
{
	srand(time(NULL));
	// for (int i = 0; i < 5; i++)
	// {
	// 	printf("Je suis le fils %d il me reste %d sec avant d'envoyer un signal a mon pere %d\n", getpid(), 5 - i, getppid());
	// 	sleep(1);
	// }
	fonction_write(10, getppid(), getpid()); // le fils écrit son pid et le pid de son pere dans un fichier

	kill(getppid(), SIGUSR1); // on envoit le signal au pere pour qu'il puisse faire la tache suivante
	while(1)
	{
		printf("\nFils %d P %d : Coucou je suis en vie ",getpid(), getppid());
		sleep(2);
		// printf("Je suis le fils %d je suis en vie\n", getpid());
		//  printf("Le nombre d'équipe est : %d\n", atoi(argv[1]));
	}
}
// Fonctions

int alea(int nbfic)
{
	int aleanum;
	aleanum = rand() % nbfic + 1;
	return aleanum;
}

int fonction_write(int max_fil, int Ppid, int Pid)
{
	char fichier[8];
	ID_PID stock_fil;
	int nb_fichier; // numéro du fichier à ouvrir
	int ecriture;	// flag d'écriture fichier
	int i = 0;
	FILE *file;
	// char file1[20];
	int read;
	printf(" Fonction write \n");
	do
	{
		nb_fichier = alea(max_fil); // il faut faire -1 sinon ça crée une erreur de segmentation fault
		printf(" Le numéro du fichier %d \n", nb_fichier);
		// printf(" PPID %d \n",Ppid);
		// printf(" PID %d \n",Pid);
		snprintf(fichier, sizeof(fichier), "%d.dat", nb_fichier); // on met le nombre que l'on vient de tirer au hasard en nom de fichier ex: 2.dat

		file = fopen(fichier, "r+b"); // on ouvre le fichier que l'on vient de tirer au hasard
		if (file == NULL)
		{
			printf(" Recherche du bon fichier \n");
			fclose(file);
			i = 0;
		}
		else
		{

			read = fread(&stock_fil, sizeof(stock_fil), 1, file);
			printf(" fread = %d\n", read);
			if (read == 1)
			{
				printf("Le fichier est déjà écrit \n");
				i = 0;
				fclose(file);
			}
			else
			{
				printf("Le fichier est vide on peut écrire \n");
				stock_fil.ppid = Ppid;
				stock_fil.pid = Pid;
				ecriture = fwrite(&stock_fil, sizeof(stock_fil), 1, file);
				i = 1;

				if (ecriture != 1)
				{
					printf(" Erreur sur l'écriture dans fichier, il se peut que le fichier n'existe pas \n ");
				}
				else
				{
					printf(" Ecriture ok \n");
				}
				fclose(file);
			}
		}
	} while (i == 0);

	return nb_fichier;
}
