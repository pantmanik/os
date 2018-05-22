#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	char command[1024];
	int i;
	strcpy(command,argv[1]);
	for (i=2; i<argc; i++)
	{
		strcat(command," ");
		strcat(command,argv[i]);

	}
	system(command);
	return 0;
}