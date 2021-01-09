#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

#define MAXSIZE 10       
int stack[MAXSIZE];     
int top = -1;

sem_t s1,s2;						//Implemented using 2 semaphores

int empty()						//To check if stack is empty
{
   	if(top == -1)
      		return 1;
   	else
      		return 0;
}

int full()						//To check if stack is full
{
   	if(top == MAXSIZE)
      		return 1;
   	else
      		return 0;
}

int at_top()						//To check value at top of stack
{
   	return stack[top];
}

int pop()						//To pop value from stack
{
   	int value;
   	if(!empty())
   	{
      		value = stack[top];
      		top = top - 1;
      		return value;
   	}
   	else
   	{
      		printf("Stack is empty!\n");
   	}
}

int push(int value)					//To push value into stack
{
   	if(!full())
   	{
      		top = top + 1;   
      		stack[top] = value;
   	}
   	else
   	{
      		printf("Stack is full!\n");
   	}
}

void* push_thread(void* p)				//Producer Thread
{
	printf("Pushing first\n");
	sem_wait(&s2);
	push(10);
	push(20);
	push(30);
	push(40);
	sem_post(&s2);
	printf("Pushing Completed\n");
	sem_post(&s1);
}

void* pop_thread(void* p)				//Consumer Thread
{
	sem_wait(&s1);
	printf("Poping atlast\n");
	sem_wait(&s2);
	pop();
	pop();
	printf("Poping Completed\n");
	sem_post(&s2);
}

int main()
{
	pthread_t t1,t2;
	sem_init(&s1,0,0);
	sem_init(&s2,0,1);
	pthread_create(&t1,NULL,push_thread,NULL);
	pthread_create(&t2,NULL,pop_thread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	if(!empty())
		printf("Top Element at %d is %d\n", top, at_top());
	sem_destroy(&s1);
	sem_destroy(&s2);
	return 0;
}
