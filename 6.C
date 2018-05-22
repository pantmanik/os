#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#define BUFF_MAX 10
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
	int shmid_mutex,shmid_full,shmid_empty,shmid_loop;
	int *mutex, *full, *empty,*loop;
	char choice;
	int i;
	int quanta=3;
	shmid_mutex = shmget(IPC_PRIVATE, sizeof(int), 0777|IPC_CREAT);
	shmid_full = shmget(IPC_PRIVATE, sizeof(int), 0777|IPC_CREAT);
	shmid_empty = shmget(IPC_PRIVATE, sizeof(int), 0777|IPC_CREAT);
	shmid_loop = shmget(IPC_PRIVATE, sizeof(int), 0777|IPC_CREAT);
	
	mutex=(int *)shmat(shmid_mutex,0,0);
	full=(int *)shmat(shmid_full,0,0);
	empty=(int *)shmat(shmid_empty,0,0);
	loop=(int *)shmat(shmid_mutex,0,0);
	*mutex=1;
	*empty=BUFF_MAX;
	*full=0;
	*loop=1;
	printf("The producer consumer problem using Semaphores.\n");
	printf("The producer can produce process when he wishes (Enter y in console to produce one, any other character to Exit)\n");
	printf("The consumer will consume a process every %d seconds\n",quanta);

	if(fork()==0)
	{
		sleep(quanta);
		do
		{
			sleep(quanta);
			wait(full);
			wait(mutex);
			printf("A process is consumed. Processes left in buffer : %d\n", *full);
			
			signal(mutex);
			signal(empty);
			
		}while(*loop);
	}
	else
	{
		do
		{
			scanf(" %c",&choice);
			printf("\n");
			wait(empty);
			wait(mutex);
			
			if(choice=='y')
			{
				printf("A process is produced! Processes left in buffer : %d\n", *full+1);
				
				signal(mutex);
				signal(full);
				
			}
			else
			{
				printf("Exiting the program!\n");
				*loop=0;
				break;
			}
		}while(*loop);
		
	}
	shmdt(full);
	shmdt(empty);
	shmdt(mutex);
	shmdt(loop);
	shmctl(shmid_mutex, IPC_RMID, 0);
	shmctl(shmid_empty, IPC_RMID, 0);
	shmctl(shmid_full, IPC_RMID, 0);
	shmctl(shmid_loop, IPC_RMID, 0);
	return 0;

}