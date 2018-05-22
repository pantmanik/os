#include<stdio.h>
#include<stdlib.h>
int main()
{
	char input;
	printf("Input y to exit process now, anything else to continue : ");
	scanf("%c",&input);
	printf("\n");
	if(input=='y')
	{
		printf("Exiting now!\n");
		exit(0);
	}
	printf("The process continues\n");
	return 0;
}