#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>

void time_handle()
{
	printf("Time Now: ");
}

void* time_thread(void* p)
{
	time_t* t=p;
	alarm(2);
	sleep(2);
	printf("%s\n",ctime(t));
}

int main()
{
	while(1)
	{
		pthread_t t1;
		signal(SIGALRM,time_handle);
		time_t s;
		time(&s);
		pthread_create(&t1,NULL,time_thread,(void*)&s);
		pthread_join(t1,NULL);
	}
}
