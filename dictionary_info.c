#define USE_MD5

#include "md5.h"
#include "hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxLength;
int nbLines;

int main (int argc, char ** argv)
{
	FILE *fp = NULL;
	
	if(argc < 1){
		fp = fopen("./Dutch_dict.txt","r");
	}else{
		fp = fopen(argv[1],"r");
	}
	
	if(fp == NULL){
		return 1;
	}
	
	printf("Reading dictionary %s\n", (argc < 1) ? "./Dutch_dict.txt" : argv[1]);
	
	nbLines = 0;
	char c;
	while ((c = fgetc(fp)) != EOF)
		if (c == '\n')
			nbLines++;
	
	printf("nbLines: %d\n", nbLines);

	rewind(fp);

	int count;
	ssize_t size;
	int chars;
	char * word;
	
	for(count = 0; count < nbLines; count++){
		word = NULL;
		size = 0;
		
		if ((chars = getline(&word,&size,fp)) == -1) {
			return 2;
		}
		
		if (maxLength < chars - 1)
			maxLength = chars - 1;
	}
	printf("Max word length: %d\n", maxLength);

	rewind(fp);

	unsigned long wordsByLength[maxLength];
	for (count = 0; count < maxLength; count++)
		wordsByLength[count] = 0;

	for(count = 0; count < nbLines; count++){
		word = NULL;
		size = 0;
		
		if ((chars = getline(&word,&size,fp)) == -1) {
			return 2;
		}
		
		if (chars > 2)
			wordsByLength[chars - 2] ++;
	}

	printf("Length\tNb\n");
	for (count = 0; count < maxLength; count++)
		printf("%d\t%d\n", count+1, wordsByLength[count]);
	
	printf("Finished reading dictionary\n");
	return 0;
}
