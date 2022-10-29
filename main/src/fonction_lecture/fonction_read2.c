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
}ID_PID;

int alea(int);
int fonction_read(int);


int fonction_read(int nbfichier)
{
	char fichier[8] = "";
	ID_PID lecturePID;
	int result=alea(nbfichier);
	FILE *file;
	
	snprintf(fichier, sizeof fichier, "%d.dat", result);
	printf("lecture du fichier %d\n",result);
	file=fopen(fichier,"r+b");
	if(file==NULL)
		printf("/!\\ fichier %d inexistant\n",result);
	else
	{
      		fread(&lecturePID.ppid,sizeof(ID_PID),1,file);
      		if(feof(file))
      		{
      			printf("Cible loupée\n");
      			lecturePID.pid=1;
      		}
      		else
      		{
    			if (lecturePID.ppid==getpid())
    			{
    				fread(&lecturePID.pid,sizeof(ID_PID),1,file);	
    			}
    			else
    			{
    				printf("Cible alliée\n");
    				lecturePID.pid=0;
    			}
    		}
    		fclose(file);
        } 

	return(lecturePID.pid);
}

int alea(int nbfic)
{
    int aleanum;
    aleanum = rand() % nbfic + 1;
    return aleanum;
}
