
/*
 * The intention of the program is to calculate the 
 * exponent as well as the number from the mantissa.
 * As it stands, everything is hardcoded which means
 * a better implementation (such as to ask to enter 
 * a number) should be put in place.
 *
 * Programmed by Adrian Meneses.
 * Date: 02/19/2020
 */

#include <stdio.h>

int main() {

	float n = 10.01;
	int found = 0;
	int counter = 0;

	if(n > 0.0 && n < 1) {
		puts("it is within 0 and 1");
	}
	else if(n >=1 && n < 2) {
		puts("n is within 1 and 2");
	}
	else {
		puts("n is negative");
	}


	n = 52.0;
	while(found != 1) {
		if((n >= 1) && (n < 2)) {
			printf("n = %.4f and E = %d\n", n, counter);
			found = 1;
		}
		else {
			n /= 2;
			printf("n = %.4f\n", n);
			counter++;
		}
	}
	
	int x = 9;
	int i = 0;
	printf("x = %d\n", x);
	for(i = 10; i >= 0; i--) {
		if(i & x) {
			printf("1");
		}
		else {
			printf("0");
		}
	}
	printf("\n");

	return 0;

}
