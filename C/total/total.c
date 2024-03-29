
/*
 * Made this program when I used to work as a server.
 * Instead of counting the bills manually up to four 
 * times, I ended up making this to speed things up
 * when going to the bank haha!
 *
 * Author: Adrian Meneses.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Args:
 *	  @ones the number of bills entered.
 *	  @fives the number of bills entered.
 *	  @tens the number of bills entered.
 *	  @twenty the number of bills entered.
 *	  @fifty the number of bills entered.
 *	  @oneHundred the number of bills entered.
 * 		Receive the value for each argument (total bills).
 *
 * Returns:
 * 		The total amount of the addition of all values.
 *
 * Notes:
 * 		Computes the total amount of every number entered and
 * 		returns it.
 */
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
 * 		None.
 *
 * Returns: 
 * 		The bill (the value) entered.
 *
 * Notes:
 * 		Makes sure the user will enter positive values
 * 		to compute the total amount.
 */
int input() {
	
	char buffer[16];
	int number = 0;

	fgets(buffer, 10, stdin);
	number = atoi(buffer);

	// Check that the number is not negative!
	if(number < 0) {
		while(number < 0) {
			printf("Can't be a negative value!\n");
			printf("Enter new amount: ");
			fgets(buffer, 10, stdin);
			number = atoi(buffer);
		}
	}

	return number;
}

/*
 * Args:
 * 		None.
 *
 * Returns:
 * 		Nothing.
 *
 * Notes:
 * 		I ask in a sequential manner each bill in ascending 
 * 		order just so the computation is correct. At the end,
 * 		I simply display the total amount to be deposited.
 */
int main() {

		int ones, fives, tens, twenty, fifty, oneHundred = 0;
		puts("Enter the number of bills:");

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

		int grandTotal = total(ones, fives, tens, twenty, fifty, oneHundred);
		printf("The total amount is: $%d\n", grandTotal);

		return 0;
}
