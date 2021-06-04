#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	// If there is no arguement then return
	if(argc==1){
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}
	char *searchterm = argv[1];
	char *lineptr = NULL;
	size_t N=0;
	// If only searchterm is specified and no file is specified
	if(argc==2){
		while(getline(&lineptr, &N, stdin) != -1){
			//Match searchterm in line input given by user
			if(strstr(lineptr, searchterm)!=NULL){
				printf("%s", lineptr);
			}
		}

		// Always free the memory pointed by line buffer <See "man getline" for details>
		free(lineptr);
	}
	// Run our grep program on each file specified
	else{	
		FILE *fp = NULL;
		for(int i=2; i<argc; i++){
			fp = fopen(argv[i], "r");
			if(fp==NULL){
				printf("wgrep: cannot open file\n");
				exit(1);
			}
			while(getline(&lineptr, &N, fp) >=0){
				// match occurence of searchterm in the line
				if(strstr(lineptr, searchterm)!=NULL){
					printf("%s", lineptr);
				}
			}
			// Always free the memory pointed by line buffer <See "man getline" for details>
			free(lineptr);
			fclose(fp);
		}
	}
	return 0;
}
