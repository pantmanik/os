#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
int main()
{
	struct stat buffer;
	int fd;
	fd=open("1gtest.txt",O_RDONLY|O_CREAT);
	stat("1gtest.txt",&buffer);
	printf("inode: %ld\n", buffer.st_ino);
	printf("owner: %u\n", buffer.st_uid);
	printf("group: %u\n", buffer.st_gid);
	printf("perms: %o\n", buffer.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
	printf("links: %ld\n", buffer.st_nlink);
	printf("size: %ld\n", buffer.st_size);
	printf("atime: %s", ctime(&buffer.st_atim.tv_sec));
	printf("mtime: %s", ctime(&buffer.st_mtim.tv_sec));
	printf("ctime: %s", ctime(&buffer.st_ctim.tv_sec));
	fd=close(fd);
	return 0;
}