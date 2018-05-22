#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include <dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<time.h>
#include<pwd.h>
#include<fcntl.h>
#include <inttypes.h>
#include"misc/miniz.c"
int isdir(char *arg)
{
	struct dirent *directoryData;
	DIR *directoryRef=opendir(arg);
	if(directoryRef==NULL)
		return 0;
	else
		return 1;
}
int isfile(char *arg)
{
	int fd=open(arg,O_RDONLY);
	if(fd==-1)
		return 0;
	else
		return 1;
}
int sep(char str[1024],char argv[10][1024])
{
	int i,j=0;
	int argc=0;
	for(int i=0;i<strlen(str);++i)
	{
		if(str[i]=='\n')
		{
			break;
		}
		else if(str[i]==' ')
		{
			if(str[i+1]!=' ')
			{
				argv[argc][j]='\0';
				j=0;
				argc++;
			}
			continue;
		}

		else
		{
			argv[argc][j]=str[i];
			j++;
		}
	}
	argv[argc][j]='\0';
	return ++argc;
}
void ls(char *arg_dir,char mode='b')
{
	struct dirent *directoryData;
	DIR *directoryRef=opendir(arg_dir);
	struct stat buffer;
	char temp[100];
	struct tm *p;
	switch(mode)
	{
		case 'b': while((directoryData=readdir(directoryRef))!=NULL)
				  {
					if(directoryData->d_name[0]!='.')
							printf("%s\n",directoryData->d_name);
				  }
				  break;
		case 'a': while((directoryData=readdir(directoryRef))!=NULL)
				{
					printf("%s\n",directoryData->d_name);
				}
				  break;
		case 'l': while((directoryData=readdir(directoryRef))!=NULL)
				{
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
				    p=localtime(&buffer.st_mtim.tv_sec);
				    strftime(temp, 100, "%b %d %H:%M", p);
				    printf(" %s",temp);
				    printf(" %s\n",directoryData->d_name);
				}
				break;
	}
}
int mv(char *src,char *dest)
{
	int err=0;
	char *tsrc, *tdest;
	struct dirent *directoryData;
	DIR *directoryRef;
	if(isfile(src))
	{
		if(isdir(dest))
		{
			if(dest[strlen(dest)-1]!='/')
				strcat(dest,"/");
			strcat(dest,src);
			rename(src,dest);
		}
		else
		{
			if(open(dest,O_RDONLY|O_CREAT)!=-1)
				rename(src,dest);
			else
				err=-1;
		}
	}
	else if(isdir(src))

	{
		directoryRef=opendir(src);
		if(src[strlen(src)-1]!='/')
			strcat(dest,"/");
		if(isdir(dest))
		{
			
			if(dest[strlen(dest)-1]!='/')
				strcat(dest,"/");
			while((directoryData=readdir(directoryRef))!=NULL)
			{
				if(directoryData->d_name[0]!='.')
				{
					strcpy(tsrc,src);
					strcpy(tdest,dest);
					strcat(tsrc,directoryData->d_name);
					strcat(tdest,directoryData->d_name);
					rename(tsrc,tdest);

				}
			}
		}
		else
			err=-1;
	}
	else
		err=-1;
	return err;
	
}
void fcp(char *src,char *dest)
{
	int fs,fd;
	char data[80];
	fs=open(src,O_RDONLY);
	fd=open(dest,O_WRONLY|O_CREAT);
	while(read(fs,data,80)>0)
		{
			write(fd,data,strlen(data));
		}
	close(fs);
	close(fd);
}
int cp(char *src,char *dest)
{
	int err=0;
	char *tsrc, *tdest;
	struct dirent *directoryData;
	DIR *directoryRef;
	if (isdir(src))
	{
		directoryRef=opendir(src);
		if(src[strlen(src)-1]!='/')
			strcat(dest,"/");
		if(isdir(dest))
		{
			if(dest[strlen(dest)-1]!='/')
				strcat(dest,"/");
			while((directoryData=readdir(directoryRef))!=NULL)
			{
				if(directoryData->d_name[0]!='.')
				{
					strcpy(tsrc,src);
					strcpy(tdest,dest);
					strcat(tsrc,directoryData->d_name);
					strcat(tdest,directoryData->d_name);
					fcp(tsrc,tdest);
				}
			}
		}
		else
			err=-1;
		
	}
	else if(isfile(src))
	{
		if(isdir(dest))
		{
			if(dest[strlen(dest)-1]!='/')
				strcat(dest,"/");
			strcat(dest,src);
			fcp(src,dest);
		}
		else
			err=-1;
	}
	else
		err=-1;
	return err;

}
int wc(char *arg)
{
	FILE *fp=fopen(arg,"r");
	int lines=0,words=0,size=0;
	char buff;
	if(fp==NULL)
		return -1;
	do
	{
		buff=fgetc(fp);
		if (feof(fp))
			break;
		if(buff==' ')
			++words;
		if(buff=='\n')
			++lines;
		++size;
	}while(1);
	words=words+lines;
	fclose(fp);
	printf("%d %d %d %s\n",lines,words,size,arg);
	return 0;
}
int grep(char *pattern,char *arg)
{
	FILE *fp=fopen(arg,"r");
	char buff[1024];
	if(fp==NULL)
		return -1;
	while(fgets(buff,sizeof(buff),fp))
	{
		if(strstr(buff,pattern)!=NULL)
		{
			printf("%s",buff);
		}
	}
	return 0;

}
int gzip(char *arg)
{
	int fd=open(arg,O_RDONLY);
	char command[1024];
	if(fd==-1)
	{
		return -1;
	}
	strcpy(command,"gzip ");
	strcat(command,arg);
	system(command);
	return 0;

}
int gunzip(char *arg)
{
	int fd=open(arg,O_RDONLY);
	char command[1024];
	if(fd==-1)
	{
		return -1;
	}
	strcpy(command,"gunzip ");
	strcat(command,arg);
	system(command);
	return 0;

}

int main()
{
	char str[1024],argv[10][1024],cwd[1024];
	char command[1024],*endptr;
	int argc,status,err,i;
	int run=1;
	struct dirent *directoryData;
	DIR *directoryRef;
	while(run)
	{
		err=0;
		getcwd(cwd,sizeof(cwd));
		printf("C shell:%s$ ",cwd);
		fgets(str,1023,stdin);
		argc=sep(str,argv);
		if(!strcmp(argv[0],"exit"))
		{
			run=0;
			break;
		}
		else if(!strcmp(argv[0],"cd"))
		{
			chdir(argv[1]);
		}
		else if(!strcmp(argv[0],"mkdir"))
		{
			err=mkdir(argv[1],S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			if(err!=0)
			{
				printf("Unable to create directory\n");
			}
		}
		else if(!strcmp(argv[0],"pwd"))
		{
			getcwd(cwd,sizeof(cwd));
			printf("%s\n",cwd);
		}
		else if(!strcmp(argv[0],"emacs"))
		{
			strcpy(command,"emacs ");
			strcat(command,argv[1]);
			system(command);
		}
		else if(!strcmp(argv[0],"ls"))
		{
			if (argc==1)
				ls(cwd);
			else
			{
				if(!strcmp(argv[1],"-a"))
				{
					ls(cwd,'a');
				}
				else if(!strcmp(argv[1],"-l"))
				{
					ls(cwd,'l');
				}
				else
				{
					printf("Invalid argument\n");
					continue;
				}
			}
		}
		else if(!strcmp(argv[0],"mv"))
		{
			err=mv(argv[1],argv[2]);
			if(err==-1)
			{
				printf("Unable to move file(s)\n");
			}
		}
		else if(!strcmp(argv[0],"more"))
		{
			strcpy(command,"more ");
			strcat(command,argv[1]);
			system(command);
		}
		else if(!strcmp(argv[0],"rm"))
		{
			for(i=1;i<argc;++i)
			{
				err=remove(argv[i]);
				if(err!=0)
				{
					printf("Unable to remove %s\n",argv[i]);
				}
			}
		}
		else if(!strcmp(argv[0],"diff"))
		{
			strcpy(command,"diff ");
			strcat(command,argv[1]);
			strcat(command," ");
			strcat(command,argv[2]);
			system(command);
		}
		else if(!strcmp(argv[0],"chmod"))
		{

			err=chmod(argv[2],strtoimax(argv[1],&endptr,8));
			if(err==-1)
			{
				printf("Unable to change permission\n");
			}
		}
		else if(!strcmp(argv[0],"wc"))
		{
			err=wc(argv[1]);
			if(err==-1)
			{
				printf("Unable to open file\n");
			}
		}
		else if(!strcmp(argv[0],"grep"))
		{
			err=grep(argv[1],argv[2]);
			if(err==-1)
			{
				printf("Unable to open file\n");
			}	
		}
		else if(!strcmp(argv[0],"cp"))
		{
			err=cp(argv[1],argv[2]);
			if(err==-1)
			{
				printf("Unable to copy file(s)\n");
			}
		}
		else if(!strcmp(argv[0],"gzip"))
		{
			err=gzip(argv[1]);
			if(err==-1)
				printf("Unable to compress file\n");
		}
		else if(!strcmp(argv[0],"gunzip"))
		{
			err=gunzip(argv[1]);
			if(err==-1)
				printf("Unable to uncompress file\n");
		}
		else if((!strcmp(argv[0],"ff"))||(!strcmp(argv[0],"lpr"))||(!strcmp(argv[0],"lpr"))||(!strcmp(argv[0],"lpq"))||(!strcmp(argv[0],"lprm"))||(!strcmp(argv[0],"genscript"))||(!strcmp(argv[0],"dvips")))
		{
			str[strlen(str)-1]='\0';
			system(str);
		}
		else
		{
			printf("unknown command: %s\n",argv[0]);
		}

	}
	return 0;
}