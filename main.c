#define USE_MD5
#include "md5.h"
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH	12

static int findText(char * buff, char * start, int length) {
	return 0;
}

int main(int argc, char ** argv) {
	if(argc < 2) {
		printf("Usage: %s <salt> <hash>", argv[0]);
		return 1;
	}
	
	char buff[strlen(argv[1]) + MAX_LENGTH + 1];
	
	memcpy(buff, argv[1], strlen(argv[1]));
	
	char *start = buff + strlen(argv[1]);
	
	int count;
	for (count = 0; count <= MAX_LENGTH; count++) {
		*(start + count) = '\0';
	}
	
	for (count = 1; count <= MAX_LENGTH; count++) {
		if (findText(buff, start, count) == 0) {
			
		}
	}
	
	return 0;
}
