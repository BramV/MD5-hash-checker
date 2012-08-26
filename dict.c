#define USE_MD5

#include "md5.h"
#include "hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define AMOUNT_OF_WORDS 220390
#define MAX_LENGTH 17

static char** ReadFile(char * Filename)
{
	FILE *fp = NULL;
	
	if(Filename == NULL){
		fp = fopen("./Dutch_dict.txt","r");
	}else{
		fp = fopen(Filename,"r");
	}
	
	if(fp == NULL){
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
	return words;
}

int main(int argc, char ** argv)
{
	if(argc < 2) {
		printf("Usage: %s <salt> <hash> [<filename>]\n", argv[0]);
		return 1;
	}
	char **words = NULL;

	if(argc < 3){
		words = ReadFile(NULL);
	}
	else{
		words = ReadFile(argv[3]);
	}

	//Need to be changed so that it uses a word out of the list
	
	unsigned char hash[17];
	if (strlen(argv[2]) == 16 * 2) {
		hex2string(argv[2], hash);
	} else if (strlen(argv[2]) == 16) {
		memcpy(hash, argv[2], strlen(argv[2]) * sizeof(char));
	}
	
	char buff[strlen(argv[1]) + MAX_LENGTH + 1];
	char * const end = buff + MAX_LENGTH * sizeof(char); //end is the part where the salt begins
	
	memcpy(end, argv[1], strlen(argv[1]) * sizeof(char));
	*(end + strlen(argv[1]) * sizeof(char)) = '\0'; //puts the \0 as last char in de buff 
	
	char * iter;
	for (iter = buff; iter < end; iter += sizeof(char)) { //sets all the char before the salt as \0
		*(iter) = '\0';
	}
	printf("line %d\n", __LINE__);
	fflush(stdout);
	int count;
	for(count = 0;count < AMOUNT_OF_WORDS; count++){
		char *start = end - strlen(words[count]);
		memcpy(start, words[count], strlen(words[count]) * sizeof(char)); //tries to copy the string on the right place in the buff
		if(check_hash(start, hash)){
			printf("PASSWORD FOUND %s", words[count]);
			return 0;
		}
	}
	printf("Sorry the password is not in the dictonary");
	return 1;
}
