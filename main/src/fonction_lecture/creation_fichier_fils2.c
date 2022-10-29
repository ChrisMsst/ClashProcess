#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

int fonction_read(int);

typedef struct ID_PID{
    int ppid;
    int pid;
}ID_PID;

int main(void)
{
    int pid, status, err,i,result;
    pid = fork();
    ID_PID ecriturePID;
    int pid1, pid2, pid3,pid4;
    //char fichier[16] = "";
    FILE *file;
    
    ecriturePID.ppid=getpid();
    if (pid == 0) {
    	file = fopen("1.dat", "w+");
  	if(file == NULL)
  	{
  		printf("Erreur le fichier n'existe pas!\n");
  	}
  	else
  	{
  		ecriturePID.pid=getpid();
  		err=fwrite(&ecriturePID.ppid,sizeof(ecriturePID),1,file);
   		err=fwrite(&ecriturePID.pid,sizeof(ecriturePID),1,file);

		if(err!=1)
		printf("\nErreur à l'écriture dans le fichier 1!\n");
  	}
  	fclose(file);
    
    	printf("2 : Je suis le fils N°1\n");
	printf("2 : Mon pid = %d \n Le pid de mon pere est : %d\n \n",getpid(), getppid());
    	//exit(3);
    	for(;;);
    	
    } else {
        printf("1 :  Je suis le pere\n ");
	printf("1 : Mon pid est = %d \n", getpid());
       // printf("2 : j ’attends la fin de mon fils\n");
	//wait(&status);
	//printf("2 : Je crée un autre fils \n\n");
	pid1 = fork();
	
	if(pid1==0)
	{
		file = fopen("2.dat", "w+");
  	if(file == NULL)
  	{
  		printf("Erreur le fichier n'existe pas!\n");
  	}
  	else
  	{
  		ecriturePID.pid=getpid();
  		err=fwrite(&ecriturePID.ppid,sizeof(ecriturePID),1,file);
   		err=fwrite(&ecriturePID.pid,sizeof(ecriturePID),1,file);;

		if(err!=1)
		printf("\nErreur à l'écriture dans le fichier 2!\n");
  	}
  	fclose(file);
  	
		printf("3 : Je suis le fils N°2\n");
		printf("3 : Mon pid=%d\n",getpid());
		printf("3 : Le pid de mon père =%d\n \n",getppid());
		//exit(1);
		for(;;);
	}
	else
	{
		//printf("3 : Je suis le Pere\n");
                //printf("3 : Mon pid=%d\n \n",getpid());
		//wait(&status);

		pid2 = fork();
		if(pid2==0)
		{
		file = fopen("3.dat", "w+");
  		if(file == NULL)
  		{
  			printf("Erreur le fichier n'existe pas!\n");
  		}
  		else
  		{
  			ecriturePID.pid=getpid();
  			err=fwrite(&ecriturePID.ppid,sizeof(ecriturePID),1,file);
   			err=fwrite(&ecriturePID.pid,sizeof(ecriturePID),1,file);

			if(err!=1)
			printf("\nErreur à l'écriture dans le fichier 3!\n");
  		}
	  	fclose(file);
	  	
			printf("4 : Je suis le fils N°3\n");
               	printf("4 : Mon pid=%d\n",getpid());
			printf("4 : le pid de mon père est = %d\n \n",getppid());
			//exit(1);
			for(;;);

		}
		else
		{
		
		//printf("4 : je suis le père mon Pid est =%d\n\n",getpid());
		//wait(&status);

		pid3 = fork();
		if(pid3 ==0)
			{
			
			file = fopen("4.dat", "w+");
  			if(file == NULL)
  			{
  				printf("Erreur le fichier n'existe pas!\n");
  			}
  			else
  			{
  				ecriturePID.pid=getpid();
  				err=fwrite(&ecriturePID.ppid,sizeof(ecriturePID),1,file);
   				err=fwrite(&ecriturePID.pid,sizeof(ecriturePID),1,file);

				if(err!=1)
				printf("\nErreur à l'écriture dans le fichier 4!\n");
  			}
  			fclose(file);
  			
				printf("5 : Je suis le fils N°4\n et mon pid est = %d \n",getpid());
				printf("5 : Le pid de mon père est = %d \n \n", getppid());
				//exit(1);
				for(;;);
			}
		else
			{
			//wait(&status);
			//printf("5 : le père mon pid est = %d \n\n", getpid());
			pid4 = fork();
			if(pid4==0)
				{
				
				file = fopen("5.dat", "w+");
  				if(file == NULL)
  				{
  					printf("Erreur le fichier n'existe pas!\n");
  				}
  				else
  				{
  					
   					ecriturePID.pid=getpid();
  					err=fwrite(&ecriturePID.ppid,sizeof(ecriturePID),1,file);
   					err=fwrite(&ecriturePID.pid,sizeof(ecriturePID),1,file);

					if(err!=1)
					printf("\nErreur à l'écriture dans le fichier 5!\n");
  				}
  				fclose(file);
				
					printf("6 : Je suis le fis N° 5\n et mon pid est = %d \n", getpid());
		                        printf("6 : Le pid de mon père est = %d \n \n", getppid());
					//exit(1);
					for(;;);
				}
			else
				{
				//printf("6 : le père  mon pid est = %d \n\n", getpid());
				//wait(&status);
				}
			
			}

		}
	}
        //printf("status = %d \n",status>>8);   
   
   	for(i=1;i<=7;i++)
   	 {
   	 	sleep(3);
   		 result=fonction_read(15);
   		 printf("result:%d\n//////////////////////////\n\n",result);
   	 }
    
    
 	wait(&status);
	printf("1 : est mort\n");
	printf("status = %d \n",status>>8);
	wait(&status);
	printf("3 : est mort\n");
	printf("status = %d \n",status>>8);
	wait(&status);
	printf("4 : est mort\n");
	printf("status = %d \n",status>>8);
	wait(&status);
	printf("5: est mort\n");
	printf("status = %d \n",status>>8);
	wait(&status);
	printf("6 : est mort\n");
	printf("status = %d \n",status>>8);
	
        printf("status = %d \n",status>>8);
    
    
    
    
     }
     
    
   /* for(i=1;i<=30;i++)
	{
	result=0;
	snprintf(fichier, sizeof fichier, "%d.dat", i);
	file=fopen(fichier,"r+b");
	if(file==NULL)
	printf("/!\\ fichier %d inexistant\n",i);
	else
	{
        fread(&result,sizeof(result),1,file);
    	printf("--> PID fils n°%d: %d\n",i,result);
    	fclose(file);
        } 
           
    	}*/
    
  return 0;
}
