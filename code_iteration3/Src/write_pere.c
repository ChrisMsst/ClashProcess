#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>



// Déclaration de fonction
int fonction_write(int num_equipe);
///////////////////////
int fonction_write(int num_equipe)
{
	char fichier[8];
	int stock_fil;
	FILE *file;
		
		file = fopen("PERE1.dat", "r+b"); // on ouvre le fichier que l'on vient de tirer au hasard
		if (file == NULL)
		{
			printf(" Erreur d'ouverture du fichier \n");
			fclose(file);
		}
		else
		{
			fread(&lecturePID.ppid, sizeof(ID_PID), 1, file); // lecture du ppid stocké dans le fichier
      			if (feof(file)) 
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
					stock_fil=getpid();
					fwrite(&stock_fil, sizeof(stock_fil), 1, file)
					fclose(file);
				}
      			}
      			else
      			{
				printf("Le fichier PERE1 est vide on peut écrire \n");
				stock_fil=getpid();
				fwrite(&stock_fil, sizeof(stock_fil), 1, file)
				fclose(file);
			}
		}
		
}
		
