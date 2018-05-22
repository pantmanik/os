#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
int main()
{
	struct dirent *directoryData;
	DIR *directoryRef=opendir("/mnt/e/manik4/os");
	if(directoryRef==NULL)
	{
		printf("Directory can't be opened\n");
		exit(-1);
	}
	else
	{
		printf("Directory opened!\n");
	}
	printf("This directory contains\n");
	while((directoryData=readdir(directoryRef))!=NULL){
		printf("%s\n",directoryData->d_name);
	}
	closedir(directoryRef);
	printf("Directory closed!\n");
	return 0;
}