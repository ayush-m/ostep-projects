#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	if(argc==1){
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}
	FILE *fp;
	int count;
	char bytes[5];	//We will be reading 5 bytes at a time (4:count of character)+(1:corresponding character)
	for(int i=1; i<argc; i++){
		fp = fopen(argv[i], "r");
		if(fp==NULL){
			printf("wunzip: cannot open file\n");
			exit(1);
		}
	   	while(fread(bytes, sizeof(int)+sizeof(char), 1, fp)>0){ //Just a hack to read 5 bytes together into a char[5] array
			count = *(int*)bytes;	//Just a hack to read first 4 bytes from char[5] array as int

			//Now print the corresponding character count times
			for(int j=0; j<count; j++){
				printf("%c", bytes[4]);
			}
		}
		fclose(fp);
	}
	return 0;
}
