#include "hex.h"

#include <stdio.h>
#include <string.h>

void string2hex(const unsigned char * const input, char * const output)
{
	int current;
	
	for (current = 0; current < 16; current++)
		sprintf (output + 2 * current * sizeof(char), "%02x", input[current]);
}

void hex2string(const char * const input, unsigned char * const output)
{
	int current;
	char buff[16 * 2 + 1];
	
	memcpy(buff, input, (16 * 2 + 1) * sizeof(unsigned char));
	
	char c;
	
	for (current = 0; current < 16; current++) {
		c = buff[(current + 1) * 2];
		buff[(current + 1) * 2] = '\0';
		
		sscanf (input + 2 * current * sizeof(char), "%02x", output + current * sizeof(unsigned char));
		
		buff[(current + 1) * 2] = c;
	}
	
	output[16 * 2] = '\0';
}

/*int main(int argc, char ** argv)
{
	char normal[17];
	int i;
	for (i = 0; i < 16; i++)
		normal[i] = 'a' + i;
	normal[16] = '\0';
	
	char hex[16 * 2 + 1];

	printf("Normal: %s\n", normal);
	string2hex(normal, hex);
	printf("Hex: %s\n", hex);
	hex2string(hex, normal);
	printf("Normal again: %s\n", normal);
}*/

/*int main(int argc, char ** argv)
{
	unsigned char normal[17];
	hex2string(argv[1], normal);

	printf("Hex: %s\n", argv[1]);
	printf("Normal: %s\n", normal);
}*/
