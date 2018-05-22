#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	printf("Current process id is %d\n",getpid());
	return 0;
}