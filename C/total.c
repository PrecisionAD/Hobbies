#include <stdio.h>

/*
 * Args:
 *
 * Notes:
 * 		Makes sure the user will enter positive values
 * 		to compute the total amount.
 */
void input() {
	
	char buffer[10];

	fgets(buffer, 9, stdin);
}


int main() {

		puts("Enter the number of bills:");
		int ones, fives, tens, twenty, fifty, oneHundred;

		printf("How many one dollar bills do you have?:\n");
		scanf("%d", &ones);
		while(ones < 0){
			printf("Error! The amount cannot be less than 0!\n");
			printf("Please enter a number higher than or equal to 0:\n");
			scanf("%d", &ones);
		}

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
