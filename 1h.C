#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
int main()
{
	DIR *directoryRef=opendir("/mnt/e/manik4/");
	if(directoryRef==NULL)
	{
		printf("Directory can't be opened\n");
		exit(-1);
	}
	else
	{
		printf("Directory opened!\n");
	}
	closedir(directoryRef);
	printf("Directory closed!\n");
	return 0;
}