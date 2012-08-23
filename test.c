#define USE_MD5
#include "md5.h"
#include <stdio.h>
#include <string.h>

static unsigned char *
md5 (const char *input) 
{
  md5_init ();
  md5_update (input, strlen (input));
  return md5_final ();
}

static void
test (char *buffer, char *expected) 
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


int main(int argc, char ** argv) {
	if(argc < 2) {
		printf("Please give an argument argument.");
	}
	
	test(argv[1], argv[2]);
	
	return 0;
}