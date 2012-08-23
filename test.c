#define USE_MD5
#include "md5.h"
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH	12

static void test (char *buffer, char *expected) 
{
  char result[16 * 3 +1];
  unsigned char* digest = md5 (buffer);
  int i;

  for (i=0; i < 16; i++)
    sprintf (result+2*i, "%02x", digest[i]);

  if (strcmp (result, expected))
    printf ("MD5(%s) failed: %s\n", buffer, result);
  else
    printf ("MD5(%s) OK\n", buffer);
}

static int findText(char * buff, char * start, int length) {
	return 0;
}

int main(int argc, char ** argv) {
	if(argc < 2) {
		printf("Usage: %s <salt> <hash>", argv[0]);
		return 1
	}
	
	char buff[strlen(argv[1]) + MAX_LENGTH + 1];
	
	memcpy(buff, argv[1], strlen(argv[1]));
	
	char *start = buff + strlen(argv[1]);
	
	int count;
	for (count = 0; count <= MAX_LENGTH; count++) {
		*(start + count) = '\0';
	}
	
	for (count = 1; count <= MAX_LENGTH; count++) {
		if (findText(buff, start, length) == 0) {
			
		}
	}
	
	return 0;
}
