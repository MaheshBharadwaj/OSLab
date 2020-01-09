#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char **argv){
	
	if(argc < 2){
		fprintf(stderr,"Insufficient Arguments Supplied!\n");
		return 1;
	}	

	DIR * dir;
	struct dirent * ent;
	
	if(argc == 2){	
			
		dir = opendir(argv[1]);	

		if(!dir){
			fprintf(stderr,"Invalid Directory\n");
			return 1;
		}

		ent = readdir(dir);
	
		while(ent){
			if(ent -> d_name[0] != '.')
				printf("%s\n",ent -> d_name);
			ent = readdir(dir);
		}
		return 0;
	}
	
	if(argc == 3){
		dir = opendir(argv[2]);	
	
		if(!dir){
			fprintf(stderr,"Invalid Directory\n");
			return 1;
		}
	
		ent = readdir(dir);
		
		if(strcmp(argv[1],"-1") == 0){				

			while(ent){
				if(ent -> d_name[0] != '.')
					printf("%s\n",ent -> d_name);
				ent = readdir(dir);
			}
		
		}else if(strcmp(argv[1],"-a") == 0){
			
			while(ent){
				printf("%s\n",ent -> d_name);
				ent = readdir(dir);
			}			
		
		}else if(strcmp(argv[1],"-r") == 0){

			char arrays[100][100];
			int counter = -1;
			
			while(ent){
				if(ent -> d_name[0] != '.')
					strcpy(arrays[++counter],ent -> d_name);
				ent = readdir(dir);
			}
			
			for(;counter > -1;counter--)
				printf("%s\n",arrays[counter]);			
						

		}else{
			fprintf(stderr,"Invalid Argument!\n");
			return 1;
		}
	}

	closedir(dir);
}
