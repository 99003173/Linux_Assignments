#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int fo,fw,len=20;
	char buf[len];
	fo=open("abc.txt",O_RDONLY);
	fw=open("pqr.txt",O_WRONLY|O_CREAT, 0666);
	read(fo, buf, len);
	write(fw, buf, strlen(buf));
	close(fo);
	close(fw);
	return 0;
}
