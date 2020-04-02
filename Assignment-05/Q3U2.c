#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
	int id;
	char *a;
	id = shmget(135, 500, IPC_CREAT | 00666);
	a = shmat(id, NULL, 0);
	while(1) {
		a[0] = '\0';
		printf("User: ");
		scanf("%[^\n]",a);
		getchar();
		if(strcmp(a,"bye") == 0) break;
		sleep(1);
		while(a[0] == '\0');
		printf("Server: %s\n", a);
		if(strcmp(a,"bye") == 0) break;
	}
	printf("Connection Ended!\n");
	shmdt(a);
	shmctl(id, IPC_RMID, NULL);
}
