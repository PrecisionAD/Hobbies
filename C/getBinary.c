
/*
 * Program will return the binary representation of a (positive) number.
 * The representation of up to 32 bits can be displayed currently.
 *
 * Programmed by Adrian Meneses.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 4294967295

int main() {
	
	char * binary;
	char buffer[33];
	int number = 0;

	printf("Enter a positive number to get its binary representation: ");
	fgets(buffer, 32, stdin);

	number = atoi(buffer);

	// Check the number is valid (positive)
	while(number < 0) {
		printf("The number %d is not valid!\n", number);
		printf("Enter a positive number: ");
		fgets(buffer, 32, stdin);
		number = atoi(buffer);
	}

	binary = malloc(sizeof(int));
	if(binary == NULL) {
		printf("Memory allocation failed! Try again!\n");
	}

	int stop = 0;
	int mask = 0;
	int counter = 0;
	int i = 32; // To save the bits from MSB to LSB
	binary[32] = '\0';

	while(stop != 1) {
		mask = number & 0x01;
		number >>= 0x01;

		// If mask is one, save the bit as 1, otherwise as 0
		if(mask == 1) { binary[i] = '1'; }
		else { binary[i] = '0'; }

		counter++;
		i--;
		if(i < 0) { stop = 1; }
	}

	printf("The binary representation is: %s\n", binary);

	free(binary);

	return 0;
}


