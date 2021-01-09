#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int status;
	int val1=fork();
	int val2;
	int val3;
	char *cfile;
	cfile="cfile.out";
	if(val1<0 || val2<0 || val3<0)
	{
		perror("fork");
		exit(1);
	}
	if(val1==0)
	{
		execl("/bin/gcc","gcc","-c","main.c",NULL);
    	}
    	else
    	{
	    	waitpid(val1, &status, 0);
	    	val2=fork();
    	}
	if(val2==0)
	{
		execl("/bin/gcc","gcc","-c","mul.c",NULL);
	}
    	else
    	{
	    	waitpid(val2, &status, 0);
	    	val3=fork();
    	}
	if(val3==0)
	{
  		execl("/bin/gcc","gcc","mul.o","main.o","-o",cfile,NULL);
  	}
    	else
    	{
	    	waitpid(val3, &status, 0);
		execl("./cfile.out", "./cfile.out", NULL);
	}
	exit(0);
}

