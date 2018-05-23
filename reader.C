#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
void wait(int *s)
{
    while(*s<=0);
    *s=*s-1;
}
void signal(int *s)
{
    *s=*s+1;
}
int main()
{
	int shmid_wrt, shmid_mutex, shmid_readcount,loop=1;
	int *wrt,*mutex,*readcount;
	char choice;
	key_t key_wrt = 12345, key_mutex=12346, key_readcount=12347;

	shmid_wrt=shmget(key_wrt, sizeof(int), 0666|IPC_CREAT);
	shmid_mutex=shmget(key_mutex, sizeof(int), 0666|IPC_CREAT);
	shmid_readcount=shmget(key_readcount, sizeof(int), 0666|IPC_CREAT);


	wrt=(int *)shmat(shmid_wrt,0,0);
	mutex=(int *)shmat(shmid_mutex,0,0);
	readcount=(int *)shmat(shmid_readcount,0,0);
	
	printf("Enter r to start reading, anything else to exit : ");
	while(loop)
	{
		scanf(" %c", &choice);
		if(choice=='r')
		{	
			wait(mutex);
			++*readcount;
			if(*readcount==1)
				wait(wrt);
			signal(mutex);
			printf("Enter s to stop reading, anything else to exit : ");
			scanf(" %c",&choice);
			if(choice=='s')
			{
				printf("Reading stopped. Enter r to read again, anything else to exit : ");
			}
			else
				loop=0;
			wait(mutex);
			--*readcount;
			if(*readcount==0)
				signal(wrt);
			signal(mutex);
		}
		else
			loop=0;
	}
	

	shmdt(wrt);
	shmctl(shmid_wrt, IPC_RMID, 0);
	shmdt(mutex);
	shmctl(shmid_mutex, IPC_RMID, 0);
	shmdt(readcount);
	shmctl(shmid_readcount, IPC_RMID, 0);
	return 0;
}