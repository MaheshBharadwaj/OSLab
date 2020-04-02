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
	char *a;
	int id = shmget(135, 500, IPC_CREAT | 00666);
	a = shmat(id, NULL, 0);
	while(1) {
		while(a[0] == '\0');
		printf("User: %s\n", a);
		if(strcmp(a,"bye") == 0) break;
		a[0] = '\0';
		printf("You: ");
		scanf("%[^\n]",a);
		getchar();
		if(strcmp(a,"bye") == 0) break;
		sleep(1);
	}
	printf("Connection Ended!\n");
	shmdt(a);
	shmctl(id, IPC_RMID, NULL);
}
