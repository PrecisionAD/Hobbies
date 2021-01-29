#include <stdio.h>
#include <stdlib.h>

/*
 * Args:
 *
 * Notes:
 * 		Makes sure the user will enter positive values
 * 		to compute the total amount.
 */
int input() {
	
	char buffer[10];
	int number = 0;

	fgets(buffer, 9, stdin);
	number = atoi(buffer);

	if(number < 0) {
		while(number < 0) {
			printf("Can't be a negative value!\n");
			printf("Enter new amount: ");
			fgets(buffer, 9, stdin);
			number = atoi(buffer);
		}
	}

	return number;

}

/*
 * Main
 */
int main() {

		puts("Enter the number of bills:");
		int ones, fives, tens, twenty, fifty, oneHundred;

		// This should be on a look or maybe a switch?
		printf("How many one dollar bills do you have?:\n");
		scanf("%d", &ones);
		while(ones < 0){
			printf("Error! The amount cannot be less than 0!\n");
			printf("Please enter a number higher than or equal to 0:\n");
			scanf("%d", &ones);
		}

		// Need to change the input format to fgets instead of scanf
		printf("How many five dollar bills?\n");
		scanf("%d", &fives);

		printf("How many ten dollar bills?\n");
		scanf("%d", &tens);

		printf("How many twenty dollar bills?\n");
		scanf("%d", &twenty);

		printf("How many fifty dollar bills?\n");
		scanf("%d", &fifty);

		printf("How many one hundred dollar bills?\n");
		scanf("%d", &oneHundred);

		// Need to make a function for this computation
		int totalFives, totalTens, totalTwenty, totalFifty, totalHundred;
		totalFives = fives * 5;
		totalTens = tens * 10;
		totalTwenty = twenty * 20;
		totalFifty = fifty * 50;
		totalHundred = oneHundred * 100;

		int grandTotal = ones + totalFives + totalTens + totalTwenty + totalFifty + totalHundred;
		printf("The total amount is: $%d\n", grandTotal);

		return 0;

}
