#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char **argv){
	char choice;	
	int source_d;
	int dest_d;	
	
	
	if(argc < 3){
		printf("Insufficient Arguments!\n");
		return 1;
	}
	
	
	if(argc == 4){	
		source_d = open(argv[2],O_RDONLY);

		if(strcmp(argv[1],"-i") == 0){
		printf("Are you sure you want to copy? Y/N ");
		scanf("%c",&choice);

			if(!(choice == 'y' || choice == 'Y'))
				return 0;
		
		}else if(strcmp(argv[1],"-f") == 0){

			;

		}else if(strcmp(argv[1],"-n") == 0){

			dest_d = open(argv[3],O_RDONLY);

			if( dest_d != -1 ){ //File Exists
				printf("File exists!Quitting!\n");
				close(dest_d);
				return 0;
			}
		
		}else if(strcmp(argv[1],"-v") == 0){
		
			printf("\'%s\' -> \'%s\'\n",argv[2],argv[3]);

		}else{
			fprintf(stderr,"Invalid Arguments [ -n , -i ,-f ,-v supported]!\n");
			return 1;
		}
		creat(argv[3],S_IRWXU);
		dest_d = open(argv[3],O_RDWR);
			
	}

	if (argc == 3){
		source_d = open(argv[1],O_RDONLY);
		creat(argv[2],S_IRWXU);
		dest_d = open(argv[2],O_RDWR);	
	}	
	
	if(source_d == -1 || dest_d == -1){
		fprintf(stderr,"Critical Error!\n");
		return 1;
	}		

	char buffer;

	while(read(source_d,&buffer,1))
		write(dest_d,&buffer,1);

	close(source_d);
	close(dest_d);
	
}
