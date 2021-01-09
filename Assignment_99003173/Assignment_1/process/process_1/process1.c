#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int val,stat;
	printf("Enter command:");
	char cmd[100];
	scanf("%[^\n]s\n",cmd);
	val=fork();
	if(val<0)
	{
		perror("fork");
		exit(1);
	}
	if(val==0)
	{
    		execl("/bin/sh","sh","-c",cmd,NULL) ; 
	}
	else	
	{
		waitpid(val, &stat, 0);
		printf("\nExit Status %d", WEXITSTATUS(stat));
	}
	exit(0);
}
