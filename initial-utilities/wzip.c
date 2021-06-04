#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
	if(argc==1){
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}
	FILE *fp;
	int ch, count, candidate;
	bool first = true;	//It represents if reading first ever character of a file
	for(int i=1; i<argc; i++){
		fp = fopen(argv[i], "r"); 
		if(fp==NULL){
			printf("wzip: cannot open file\n");
			exit(1);
		}
		if(first){
			candidate=getc(fp);
			count=1;
			first = false;	//Setting it to false since now on non first characters will be read
		}
		if(candidate!=EOF){
			while((ch=getc(fp))!=EOF){
				if(ch==candidate) count++;
				else{
					fwrite(&count, sizeof(int), 1, stdout);
					fwrite(&candidate, sizeof(char), 1, stdout);
					//printf("%c %d hex(%x)\n", candidate, count, candidate);
					candidate = ch;
					count=1;
				}
			}
		}
		fclose(fp);
	}
	fwrite(&count, sizeof(int), 1, stdout);
	fwrite(&candidate, sizeof(char), 1, stdout);
	return 0;
}
