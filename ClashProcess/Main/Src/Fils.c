#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

int main(void)
{
    for(i=1;i<=30;i++)
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
}