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
	int shmid_wrt,*wrt,loop=1;
	key_t key_wrt = 12345;
	char choice;
	shmid_wrt=shmget(key_wrt, sizeof(int), 0666|IPC_CREAT);
	wrt=(int *)shmat(shmid_wrt,0,0);
	
	printf("Enter w to start writing, anything else to exit : ");
	while(loop)
	{
		
		scanf(" %c",&choice);
		if(choice=='w')
		{
			wait(wrt);
			printf("Enter s to stop writing, anything else to exit : ");
			scanf(" %c",&choice);
			signal(wrt);
			if(choice=='s')
			{
				printf("Writing stopped. Enter w to start writing again, anything else to exit : ");
				continue;
			}
			else
				loop=0;
		}
		else
			loop=0;
	}

	shmdt(wrt);
	shmctl(shmid_wrt, IPC_RMID, 0);
	return 0;
}