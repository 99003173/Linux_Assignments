#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MY_FIFO_FILE "CS_FIFO" 			//CS_FIFO file is created

int main()	
{
	int fc, exit, recv_bytes;
   	char sent_msg[80], recv_msg[80];

   	printf("CLIENT: Chat Away!! To stop, send \"OK,BYE.\"\n\n");
   	fc = open(MY_FIFO_FILE, O_CREAT|O_RDWR);
   
   	while (1)
   	{
   		printf("I AM SENDING BACK: ");
      		fgets(sent_msg, sizeof(sent_msg), stdin);
      		sent_msg[strlen(sent_msg) - 1] = '\0';
         	write(fc, sent_msg, strlen(sent_msg));
      		exit = strcmp(sent_msg, "OK,BYE.");

      		if (exit != 0)
      		{
         		recv_bytes = read(fc, recv_msg, sizeof(recv_msg));
         		recv_msg[recv_bytes] = '\0';
         		printf("SERVER SENT ME: \"%s\" \n", recv_msg);
      		}
      		
      		else
      		{
         		close(fc);
         		break;
      		}
   	}
   	return 0;
}
