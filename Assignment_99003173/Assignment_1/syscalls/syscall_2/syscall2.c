#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int fo,max=100;
	char ch[max];
	fo=open("msg.txt",O_RDONLY);
	read(fo, ch, max);
	int c=0,w=0,l=0;
    	for(int i=0;i<strlen(ch);i++)
    	{
        	c++;
        	if (ch[i] == '\n' || ch[i] == '\0')
            		l++;
        	if (ch[i] == ' ' || ch[i] == '\t' || ch[i] == '\n' || ch[i] == '\0')
            		w++;
    	}
    	printf("Lines=%d, Words=%d, Characters=%d",l,w,c);
	close(fo);
	return 0;
}
