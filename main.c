#define USE_MD5

#include "md5.h"
#include "hex.h"

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH	4
#define MIN_LENGTH	1

static bool findText_internal(const char * const start, char * const current, const int length, const unsigned char * const hash)
{
	if (length == 0)
		return check_hash(start, hash);
	
	char c;
	
	for (c = 'a'; c <= 'z'; c++) {
		*current = c;
		if (findText_internal(start, current + sizeof(char), length - 1, hash))
			return true;
	}
	
	for (c = 'A'; c <= 'Z'; c++) {
		*current = c;
		if (findText_internal(start, current + sizeof(char), length - 1, hash))
			return true;
	}
	
	return false;
}

static bool findText(char * const start, const int length, const unsigned char * const hash)
{
	return findText_internal(start, start, length, hash);
}

int main(int argc, char ** argv)
{
	if(argc < 2) {
		printf("Usage: %s <salt> <hash>\n", argv[0]);
		return 1;
	}
	
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
	
	int count;
	for (count = MIN_LENGTH; count <= MAX_LENGTH; count++) {
		if (findText(end - count * sizeof(char), count, hash)) {
			printf("Match found: %s\n", end - count * sizeof(char));
			*end = '\0';
			printf("Matching string: %s\n", end - count * sizeof(char));
			return 0;
		} else {
			printf("Tried all passwords with length %d.\n", count);
		}
	}
	
	printf("Failed to find any matching password between lengths %d and %d.\n", MIN_LENGTH, MAX_LENGTH);
	return 2;
}
