#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
	if(fork()==0)
	{
		printf("Started child process\n");
		printf("Exiting child now\n");
	}
	else
	{
		printf("Started parent process\n");
		wait(NULL);
		printf("All children processes exited\n");
	}
	return 0;
}