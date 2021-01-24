/*
 * Program will return the binary representation of a (positive) number.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	
	char * binary;
	char buffer[33];
	int number = 0;

	printf("Enter a number to get its binary representation: ");
	fgets(buffer, 32, stdin);

	printf("\nThe number entered was: %s\n", buffer);
	
	number  = atoi(buffer);
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


