#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
void strupr(char *a)
{
	for(int i = 0; a[i] != '\0'; i++)
		a[i] -= (a[i] >= 'a' && a[i] <= 'z') ? 32 : 0;
}
int main()
{
	int pid, id;
	char *a, *b;
	id = shmget(111, 50, IPC_CREAT | 00666);
	pid = fork();
	if(pid > 0)
	{
		printf("Parent Process\n");
		a = shmat(id, NULL, 0);
		a[0] = '\0';
		printf("Enter a string: ");
		scanf("%[^\n]", a);
		wait(NULL);
		shmdt(a);
	}
	else
	{
		b = shmat(id, NULL, 0);
		while(b[0] == '\0');
		printf("\nChild Process:\n");
		strupr(b);
		printf("Uppercase: %s\n", b);
		shmdt(b);
	}
	shmctl(id, IPC_RMID, NULL);
}
