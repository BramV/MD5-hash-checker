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
	maxLength = 0;
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
	}
	
	printf("Max word length: %d\nFinished reading dictionary\n", maxLength);
	return words;
}

static char switchCase(char c)
{
	char d = toupper(c);
	return (d == c) ? tolower(c) : d;
}

static bool checkWord_internal(const char * const start, char * current, int length, const char * const hash)
{
	if (length == 0) {
		return check_hash(start, hash);
	}

	char c = *current;
	*current = switchCase(*current);
	if (checkWord_internal(start, current + sizeof(char), length - 1, hash))
		return true;

	*current = c;
	return checkWord_internal(start, current + sizeof(char), length - 1, hash);
}

static bool checkWord(char * start, int length, const char * const hash, bool caseSensitive)
{
	if (caseSensitive & length < 15)
		return checkWord_internal(start, start, length, hash);
	else
		return check_hash(start, hash);
}

static bool checkFile(char * filename, const char hash[17], const char * const salt, bool caseSensitive, int *returnValue)
{
	char ** words = NULL;
	*returnValue = 0;

	words = ReadFile(filename);
	if (words == NULL) {
		printf("Invalid file: %s\n", filename);
		*returnValue = 1;
		return false;
	}

	char buff[strlen(salt) + maxLength + 1];
	char * const end = buff + maxLength * sizeof(char); //end is the part where the salt begins
	
	memcpy(end, salt, strlen(salt) * sizeof(char));
	*(end + strlen(salt) * sizeof(char)) = '\0'; //puts the \0 as last char in de buff 
	
	char * iter;
	for (iter = buff; iter < end; iter += sizeof(char)) { //sets all the char before the salt as \0
		*(iter) = '\0';
	}

	printf("Checking for password ");
	fflush(stdout);

	int count;
	char *start;
	int length;
	for(count = 0;count < nbLines; count++){
		if ((count << (sizeof(int) * 8 - 10)) == 0) {
			printf(".");
			fflush(stdout);
		}

		length = strlen(words[count]);
		start = end - length;
		memcpy(start, words[count], length * sizeof(char)); //tries to copy the string on the right place in the buff
		
		if(checkWord(start, length, hash, caseSensitive)) {
			printf("\nMatch: %s\nPassword: %s\n", start, words[count]);
			return true;
		}
	}
	printf("\nThe password is not in the dictonary.\n\n");
	return false;	
}

int main(int argc, char ** argv)
{
	if(argc < 3 || argv[3] == NULL) {
		printf("Usage: %s [-i] <salt> <hash> <filename> [filename...]\n", argv[0]);
		return 1;
	}

	bool caseSensitive;
	int argOffset;
	if (!strcmp(argv[1], "-i")) {
		caseSensitive = true;
		argOffset = 1;
		if (argc < 4 || argv[4] == NULL) {
			printf("Usage: %s [-i] <salt> <hash> <filename> [filename...]\n", argv[0]);
			return 1;
		}
		printf("Running case insensitive check...");
	} else {
		caseSensitive = false;
		argOffset = 0;
	}

	unsigned char hash[17];
	if (strlen(argv[2 + argOffset]) == 16 * 2) {
		hex2string(argv[2 + argOffset], hash);
	} else if (strlen(argv[2 + argOffset]) == 16) {
		memcpy(hash, argv[2 + argOffset], strlen(argv[2 + argOffset]) * sizeof(char));
	} else {
		printf("Invalid hash\n");
		return 4;
	}
	
	int count;
	int retVal;
	for (count = argOffset + 3; count < argc; count++) {
		if (argv[count] == NULL) continue;
		printf("Checking dictionary %s\n", argv[count]);
		if (checkFile(argv[count], hash, argv[1 + argOffset], caseSensitive, &retVal)) {
			return 0;
		} else if (retVal != 0) {
			return retVal;
		}
	}
	return 0;
}
