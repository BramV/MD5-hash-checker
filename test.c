#include "md5.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
	if(argc < 2) {
		printf("Usage: %s: <plaintext> <hash>\n", argv[0]);
		return 1;
	}

	test(argv[1], argv[2]);

	return 0;
}
