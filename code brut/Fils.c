#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	for (int i = 0; i < 5; i++)
	{
		printf("Je suis le fils %d il me reste %d sec avant d'envoyer un signal a mon pere %d\n", getpid(), 5 - i, getppid());
		sleep(1);
	}

	kill(getppid(), SIGUSR1); // on envoit le signal au pere pour qu'il puisse faire la tache suivante
	for (;;)
	{
		printf("Je suis le fils %d je suis en vie\n", getpid());
		// printf("Le nombre d'équipe est : %d\n", atoi(argv[1]));
		sleep(2);
	}
}