#include<stdio.h>
#include <unistd.h>
int main(int argv,char *args[])
{
	printf("This is a program called by execv from %s\n",args[1]);
	return 0;
}