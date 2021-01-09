#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int val,stat;
	val=fork();
	char *cfile;
	cfile="program.out";
	if(val<0)
	{
		perror("FORK");
		exit(1);
	}
	if(val==0)
	{ 
    		execl("/bin/gcc","gcc","-c","evenodd.c",NULL) ; 
	}
	else	
	{
		waitpid(val, &stat, 0); 
		execl("/bin/gcc","gcc","evenodd.o","-o",cfile,NULL);
	}
	exit(0);
}
