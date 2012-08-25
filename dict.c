#define USE_MD5

#include "md5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define AMOUNT_OF_WORDS 220390

static char** ReadFile(char * Filename)
{
	FILE *fp;
	
	if(Filename == NULL){
		fp = fopen("./Dutch_dict.txt","r");
	}else{
		fp = fopen(Filename,"r");
	}
	
	if(fp = NULL){
		return NULL;
	}
	
	char **words = malloc(sizeof(char*)*AMOUNT_OF_WORDS);
	int count;
	int size = 3;
	for(count = 0; count < AMOUNT_OF_WORDS; count++){
		char *word = malloc((sizeof(char)*size) + 1);
		getline(&word,&size,fp);
		words[count] = word;
	}
	
}

static bool findText(char * const start, const int length, const unsigned char * const hash)
{
	return findText_internal(start, start, length, hash);
}

int main(int argc, char ** argv)
{
	if(argc < 2) {
		printf("Usage: %s <salt> <hash> [<filename>]\n", argv[0]);
		return 1;
	}
	char **words = ReadFile(NULL);
	
	//Need to be changed so that it uses a word out of the list
	
	unsigned char hash[17];
	if (strlen(argv[2]) == 16 * 2) {
		hex2string(argv[2], hash);
	} else if (strlen(argv[2]) == 16) {
		memcpy(hash, argv[2], strlen(argv[2]) * sizeof(char));
	}
	
	char buff[strlen(argv[1]) + MAX_LENGTH + 1];
	char * const end = buff + MAX_LENGTH * sizeof(char);
	
	memcpy(end, argv[1], strlen(argv[1]) * sizeof(char));
	*(end + strlen(argv[1]) * sizeof(char)) = '\0';
	
	char * iter;
	for (iter = buff; iter < end; iter += sizeof(char)) {
		*(iter) = '\0';
	}

	return 2;
}
