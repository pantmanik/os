#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argv,char *args[])
{
	char *message[]={"./1bDemot",args[0],NULL};
	execv(message[0],message);
	printf("\nThis should not print\n");
	return 0;
}