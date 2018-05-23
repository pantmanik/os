#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
int main()
{
	int shmid_wrt, shmid_mutex, shmid_readcount;
	int *wrt,*mutex,*readcount;
	key_t key_wrt = 12345, key_mutex=12346, key_readcount=12347;

	shmid_wrt=shmget(key_wrt, sizeof(int), 0666|IPC_CREAT);
	shmid_mutex=shmget(key_mutex, sizeof(int), 0666|IPC_CREAT);
	shmid_readcount=shmget(key_readcount, sizeof(int), 0666|IPC_CREAT);


	wrt=(int *)shmat(shmid_wrt,0,0);
	mutex=(int *)shmat(shmid_mutex,0,0);
	readcount=(int *)shmat(shmid_readcount,0,0);
	
	*wrt=1;
	*mutex=1;
	*readcount=0;
	
	pause();

	shmdt(wrt);
	shmctl(shmid_wrt, IPC_RMID, 0);
	shmdt(mutex);
	shmctl(shmid_mutex, IPC_RMID, 0);
	shmdt(readcount);
	shmctl(shmid_readcount, IPC_RMID, 0);
	return 0;
}