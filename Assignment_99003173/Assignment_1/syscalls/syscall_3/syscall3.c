#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int pid,c;
	printf("Enter PID & its usage:");
	scanf("%d",&pid);
	printf("What to do with it [1-k|2-q|3-a|4-s|5-i]");
	scanf(" %d",&c);
	switch(c)
	{
		case 1:printf("Kill Process\n");
			 kill(pid, 9);
			 break;
		case 2:printf("Quit Process\n");
			 kill(pid, 3);
			 break;
		case 3:printf("Abort Process\n");
			 kill(pid, 6);
			 break;
		case 4:printf("Stop Process\n");
			 kill(pid, 6);
			 break;
		case 5:printf("Interupt Process\n");
			 kill(pid, 2);
			 break;
		default:;
	}
}
