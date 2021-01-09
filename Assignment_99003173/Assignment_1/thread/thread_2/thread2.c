#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 1000

void* maximum(void* p)
{
	int* a=p;
	int i, max = a[0];
	for (i = 1; i < MAX; i++)
	{ 
		if (a[i] > max) 
			max = a[i];
    	}
    	int status = max;
    	pthread_exit((void*)status);
}

void* minimum(void* p)
{
	int* a=p;
	int i, min = a[0];
	for (i = 1; i < MAX; i++)
	{ 
		if (a[i] < min) 
			min = a[i];
    	}
    	int status = min;
    	pthread_exit((void*)status);
}

int main()
{
    int arr[MAX],i;
    pthread_t t1,t2;
    void* max;
    void* min;
    for(i=0;i<MAX;i++)
    	arr[i]=i;
    pthread_create(&t1, NULL, maximum, (void*)arr); 
    pthread_create(&t2, NULL, minimum, (void*)arr);
    pthread_join(t1,&max);
    pthread_join(t2,&min);
    printf("Maximum Element is : %d\n", (int)max); 
    printf("Minimum Element is : %d\n", (int)min); 
    return 0; 
}
