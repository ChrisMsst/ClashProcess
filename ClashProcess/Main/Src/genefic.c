#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
  FILE *fp;
  int i=0;
  char fichier[16] = "";
  
	for(i=1;i<=10;i++)
	{
	snprintf(fichier, sizeof fichier, "%d.dat", i);
	fp=fopen(fichier,"r+b");
	if(fp==NULL)
	{
		printf("Creation du fichier %d.dat...\n",i);
		fp=fopen(fichier,"w+b");
		if(fp==NULL)
		{
			printf("Erreur d'ouverture du fichier %d en w+b ! Fermeture du programme ...\n",i);
			
			exit(0);
		}
		fclose(fp);
	}
	else
	{
		printf("Le fichier %d existe déjà\n",i);
		fclose(fp);
	}
	}
 
}
