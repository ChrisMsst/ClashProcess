#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>


int main(void)
{
    int pid, status;
    pid = fork();
    int pid1, pid2, pid3,pid4;
    if (pid == 0) {
        printf(" 1 : Je suis le fils N°1\n");
	printf("1 : Mon pid = %d \t Le pid de mon pere est : %d\n \n",getpid(), getppid());
        exit(3);
    } else {
        printf("2 :  Je suis le pere\n ");
	printf("2 : Mon pid est = %d \n", getpid());
       // printf("2 : j ’attends la fin de mon fils\n");
	wait(&status);
	//printf("2 : Je crée un autre fils \n\n");
	pid1 = fork();
	if(pid1==0)
	{
		printf("3 : Je suis le fils N°2\n");
		printf("3 : Mon pid=%d\n",getpid());
		printf("3 : Le pid de mon père =%d\n \n",getppid());
		exit(1);
	}
	else
	{
		//printf("3 : Je suis le Pere\n");
                //printf("3 : Mon pid=%d\n \n",getpid());
		wait(&status);

		pid2 = fork();
		if(pid2==0)
		{
			printf("4 : Je suis le fils N°3\n");
               		printf("4 : Mon pid=%d\n",getpid());
			printf("4 : le pid de mon père est = %d\n \n",getppid());
			exit(1);

		}
		else
		{
		
		//printf("4 : je suis le père mon Pid est =%d\n\n",getpid());
		wait(&status);

		pid3 = fork();
		if(pid3 ==0)
			{
				printf("5 : Je suis le fils N°4 et mon pid est = %d \n",getpid());
				printf("5 : Le pid de mon père est = %d \n \n", getppid());
				exit(1);
			}
		else
			{
			wait(&status);
			//printf("5 : le père mon pid est = %d \n\n", getpid());
			pid4 = fork();
			if(pid4==0)
				{
					printf("6 : Je suis le fis N° 5 et mon pid est = %d \n", getpid());
		                        printf("6 : Le pid de mon père est = %d \n \n", getppid());
					exit(1);
				}
			else
				{
				//printf("6 : le père  mon pid est = %d \n\n", getpid());
				wait(&status);
				}
			
			}

		}
	}
        printf("status = %d \n",status>>8);
    }
  return 0;
}
