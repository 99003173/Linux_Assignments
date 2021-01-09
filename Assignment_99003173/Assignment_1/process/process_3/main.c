#include "mul.h"
#include <stdio.h>

int main()
{
	int a,b;
	printf("Enter numbers");
	scanf("%d %d",&a,&b);
	printf("product is %d",mul(a,b));
	return 0;
}
