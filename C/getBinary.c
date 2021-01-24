#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Program to return the binary representation of a number. */
int main() {
	
	char * binary;
	char buffer[33];
	int number = 0;

	printf("Enter a number to get its binary representation\n");
	fgets(buffer, 32, stdin);

	printf("\nThe number entered was: %s\n", buffer);
	
	number  = atoi(buffer);
	binary = malloc(sizeof(int) + 1);
	if(binary == NULL) {
		printf("Memory allocation failed! Try again!\n");
	}

	int stop = 0;
	int mask = 0;
	int counter = 0;
	int i = sizeof(binary) - 1;
	i = 39;
	binary[40] = '\0';
	printf("size of binary is = %d\n", i);
	printf("i = %d\n", i);

	while(stop != 1) {
		mask = number & 0x01;
		number >>= 0x01;

	//	if((counter % 4) == 0) { binary[i - 1] = ' '; } 
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


