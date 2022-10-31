#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

typedef struct ID_PID{
int ppid;
int pid;
}
ID_PID;

// Déclaration de fonction
int fonction_write(int max_fil,int Ppid,int Pid);
int alea(int nbfic);

// Fonctions

int alea(int nbfic)
{
    int aleanum;
    aleanum = rand() % nbfic + 1;
    return aleanum;
}
/////////////////
int fonction_write(int max_fil,int Ppid,int Pid)
{
	char fichier[8];
	ID_PID stock_fil;
	int nb_fichier; // numéro du fichier à ouvrir
	int ecriture; // flag d'écriture fichier
	int i=0;
	FILE *file; 
	//char file1[20];
	int read;
	printf(" Fonction write \n");
	do
	{
		nb_fichier= alea(max_fil-1); // il faut faire -1 sinon ça crée une erreur de segmentation fault
		printf(" Le numéro du fichier %d \n",nb_fichier);
		//printf(" PPID %d \n",Ppid);
		//printf(" PID %d \n",Pid);
		snprintf(fichier, sizeof(fichier), "%d.dat", nb_fichier);
		
		file = fopen(fichier,"r+b");
		if(file == NULL)
			{
				printf(" Recherche du bon fichier \n"); 
				fclose(file);
				i=0;
				
			}
			
		else
			{ 
			
				read = fread(&stock_fil,sizeof(stock_fil),1,file);
				printf(" fread = %d\n",read);
				if(read == 1)
					{
						printf("Le fichier est déjà écrit \n");
						i=0;
						fclose(file);
					}
				else
					{	
						printf("Le fichier est vide on peut écrire \n");
						stock_fil.ppid = Ppid;
						stock_fil.pid = Pid;
						ecriture = fwrite(&stock_fil, sizeof(stock_fil),1,file);
						i=1;
						
						if(ecriture =!1)
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
	}
	while(i==0);
	
	return nb_fichier;
}

int main()
{


	ID_PID stock_fil;
	int max, write,i,j,val;
	char fichier[8];
	char fichier1[8];
	FILE *file1 = NULL;
	FILE *file = NULL;
	printf(" Fonction principale \n");
	
	    for(i=1;i<=50;i++)
		{
			
			snprintf(fichier1, sizeof fichier1, "%d.dat", i);
			file1 = fopen(fichier1,"w+b");
			fclose(file1);
			
		} 
        printf(" for = %d \n",i);
        for(j=0; j<=20; j++)
        	{
				
				max = i;
				write = fonction_write(max,30,40);
				printf(" Le numéro du fichier retourné %d \n",write);
				snprintf(fichier, sizeof(fichier), "%d.dat", write);
				file = fopen(fichier,"r+b");
				
				if(file == NULL)
					{
						printf(" Le fichier est vide ou il n'existe pas \n");
						fclose(file);
					}
					
				else
					{
						fread(&stock_fil,sizeof(stock_fil),1,file);
						printf("PPID = %d: PID = %d\n\n",stock_fil.ppid, stock_fil.pid);	
						fclose(file);
					}
					
        	}
	
    		
}








