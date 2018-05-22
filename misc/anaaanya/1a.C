#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int process=1;
int main()
{
	int pid=fork();
	if(pid==0)
		printf("This is child process\n");
	else
		printf("This is parent process\n");
	return 0;
}