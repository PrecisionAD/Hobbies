#include <stdio.h>
#include <stdlib.h>


int total(int ones, int fives, int tens, int twenty, int fifty, int oneHundred) {

		int totalFives, totalTens, totalTwenty, totalFifty, totalHundred;
		totalFives = fives * 5;
		totalTens = tens * 10;
		totalTwenty = twenty * 20;
		totalFifty = fifty * 50;
		totalHundred = oneHundred * 100;

		int grandTotal = ones + totalFives + totalTens + totalTwenty + totalFifty + totalHundred;

		return grandTotal;
}


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
		int ones, fives, tens, twenty, fifty, oneHundred = 0;

		printf("How many one dollar bills do you have?:\n");
		ones = input();

		printf("How many five dollar bills?\n");
		fives = input();

		printf("How many ten dollar bills?\n");
		tens = input();

		printf("How many twenty dollar bills?\n");
		twenty = input();

		printf("How many fifty dollar bills?\n");
		fifty = input();

		printf("How many one hundred dollar bills?\n");
		oneHundred = input();

		// Need to make a function for this computation
	/*	int totalFives, totalTens, totalTwenty, totalFifty, totalHundred;
		totalFives = fives * 5;
		totalTens = tens * 10;
		totalTwenty = twenty * 20;
		totalFifty = fifty * 50;
		totalHundred = oneHundred * 100;

		int grandTotal = ones + totalFives + totalTens + totalTwenty + totalFifty + totalHundred;*/
		int grandTotal = total(ones, fives, tens, twenty, fifty, oneHundred);
		printf("The total amount is: $%d\n", grandTotal);

		return 0;

}
