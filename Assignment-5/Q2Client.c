
#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
int main()
{
	int id;
	char *a;
	char filename[100];
	id = shmget(126, 50, IPC_CREAT | 00666);
	a = shmat(id, NULL, 0);
	a[0] = '\0';
	printf("Enter file name: ");
	scanf("%s",filename);
	strcpy(a,filename);
	strcat(filename,"-copy");
	sleep(3);
	while(a[0] == '\0');
	int fd = open(filename,O_WRONLY | O_CREAT,S_IRWXU);
	printf("%s", a);
	write(fd,a,strlen(a));
	shmdt(a);
	shmctl(id, IPC_RMID, NULL);
	close(fd);
	return 0;
}
