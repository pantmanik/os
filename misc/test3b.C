#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<pwd.h>
#include <dirent.h>
int main()
{
	struct dirent *directoryData;
	DIR *directoryRef=opendir(arg_dir);
	struct stat buffer;
	while((directoryData=readdir(directoryRef))!=NULL){
		stat(directoryData->d_name,&buffer);
		printf( (S_ISDIR(buffer.st_mode)) ? "d" : "-");
	    printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
	    printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
	    printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
	    printf(" %ld", buffer.st_nlink);
	    printf(" %s",getpwuid(buffer.st_uid)->pw_name);
	    printf(" %s",getpwuid(buffer.st_gid)->pw_name);
	    printf(" %ld", buffer.st_size);
	    printf(" %s", ctime(&buffer.st_mtim.tv_sec));
	    printf(" %s",directoryData->d_name);
	}
	return 0;
}