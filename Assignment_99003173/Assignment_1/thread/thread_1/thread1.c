#include<pthread.h>
#include<stdio.h>

#define SUB_MAX 100
#define MAX 1000

void* temp_sum(void* pv)
{
	int* arr=pv;
	int i,s=0;
	for(i=0;i<SUB_MAX;i++)
		s+=arr[i];
	printf("Thread sum = %d\n",s);	//Sum inside each thread's(Concurrent o/p)
    	int status = s;
	pthread_exit((void*)status);
}

int main()
{
	pthread_t t[10];
	int a[MAX],i,sum=0;
	void* status;
	for(i=0;i<MAX;i++)
		a[i]=i;
	for(i=0;i<10;i++)
		pthread_create(&t[i],NULL,temp_sum,(void*)&a[i*SUB_MAX]);
	for(i=0;i<10;i++)
	{
		pthread_join(t[i],&status);
		sum+=(int)status;
		printf("Inside main sum%d = %d\n",i,(int)status);	//Sum of each thread returned after exit of thread
	}
	printf("TOT %d\n",sum);
	return 0;
}
