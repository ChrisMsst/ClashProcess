#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>


typedef struct ID_PID{ 	// structure pour lire correctement les fichiers binaire
    int ppid;
    int pid;
}ID_PID;

int alea(int); 
int fonction_read(int);


int fonction_read(int nbfichier)
{
	char fichier[8] = ""; 	//chaine de caractère qui va varier en fonction du fichier que l'on veut ouvrir 
	ID_PID lecturePID;
	int result=alea(nbfichier);
	FILE *file;
	
	snprintf(fichier, sizeof fichier, "%d.dat", result); //fonction qui permet de faire varié la chaine de caractère en fonction du result retourné par la variable aléatoire
	printf("lecture du fichier %d\n",result);
	file=fopen(fichier,"r+b");
	if(file==NULL)
		printf("/!\\ fichier %d inexistant\n",result);
	else
	{
      		fread(&lecturePID.ppid,sizeof(ID_PID),1,file); // lecture du ppid stocké dans le fichier
      		if(feof(file)) // le fichier est vide alors:
      		{
      			printf("Cible loupée\n"); 
      			lecturePID.pid=1; // retour de la fonction sera 1
      		}
      		else
      		{
    			if (lecturePID.ppid==getpid()) // le ppid du fils trouvé est différent du pid du père qui execute cette fonction
    			{
    				fread(&lecturePID.pid,sizeof(ID_PID),1,file);	 // alors on lit le pid stocké dans le fichier
    			}
    			else
    			{
    				printf("Cible alliée\n"); 
    				lecturePID.pid=0; // sinon cela signifie que le père cible un de ses fils alors on retournera la valeur 0
    			}
    		}
    		fclose(file);
        } 

	return(lecturePID.pid);
}

int alea(int nbfic) 	// fonction qui tire un nombre aléatoire entre 1 et le nombre max de fichier binaire
{
    int aleanum;
    aleanum = rand() % nbfic + 1;
    return aleanum;
}
