#define USE_MD5

#include "md5.h"
#include "hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxLength;
int nbLines;

static char** ReadFile(char * filename)
{
	FILE *fp = NULL;
	
	if(filename == NULL){
		fp = fopen("./Dutch_dict.txt","r");
	}else{
		fp = fopen(filename,"r");
	}
	
	if(fp == NULL){
		return NULL;
	}
	
	printf("Reading dictionary %s\n", (filename == NULL) ? "./Dutch_dict.txt" : filename);
	
	nbLines = 0;
	char c;
	while ((c = fgetc(fp)) != EOF)
		if (c == '\n')
			nbLines++;
	
	printf("nbLines: %d\n", nbLines);
	rewind(fp);
	
	char **words = malloc(sizeof(char*) * nbLines);
	
	int count;
	char *word;
	ssize_t size;
	int chars;
	for(count = 0; count < nbLines; count++){
		word = NULL;
		size = 0;
		
		if ((chars = getline(&word,&size,fp)) == -1) {
			int i;
			for (i = 0; i < count; i++)
				free(words[i]);
			free(words);
			return NULL;
		}
		
		if (maxLength < (chars - 1))
			maxLength = chars - 1;
		
		word[chars - 1] = '\0';
		words[count] = word;
		
//		printf("%x\t%d\t%d\t%s\n", word, size, chars, word);
	}
	
	printf("Max word length: %d\nFinished reading dictionary\n", maxLength);
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
	
	if (words == NULL) {
		printf("Error: invalid input");
		return -1;
	}
	
	printf("\n");

	//Need to be changed so that it uses a word out of the list
	
	unsigned char hash[17];
	if (strlen(argv[2]) == 16 * 2) {
		hex2string(argv[2], hash);
	} else if (strlen(argv[2]) == 16) {
		memcpy(hash, argv[2], strlen(argv[2]) * sizeof(char));
	}
	
	char buff[strlen(argv[1]) + maxLength + 1];
	char * const end = buff + maxLength * sizeof(char); //end is the part where the salt begins
	
	memcpy(end, argv[1], strlen(argv[1]) * sizeof(char));
	*(end + strlen(argv[1]) * sizeof(char)) = '\0'; //puts the \0 as last char in de buff 
	
	char * iter;
	for (iter = buff; iter < end; iter += sizeof(char)) { //sets all the char before the salt as \0
		*(iter) = '\0';
	}

	int count;
	for(count = 0;count < nbLines; count++){
		char *start = end - strlen(words[count]);
		memcpy(start, words[count], strlen(words[count]) * sizeof(char)); //tries to copy the string on the right place in the buff
		
		if(check_hash(start, hash)){
			printf("Match: %s\nPassword: %s\n", start, words[count]);
			return 0;
		}
	}
	printf("The password is not in the dictonary.\n");
	return 2;
}
