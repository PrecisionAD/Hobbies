
/* Small program to compute an approximation of pi.
 * Currently, it will comute up to 8 correct digits.
 * Programmed by Adrian Meneses.
 */

#include <stdio.h>
#include <stdlib.h>

#define NUM 4
#define ONE_MILLION 1000000
#define TEN_BILLION 10000000
#define HUN_MILLION 100000000
#define ONE_BILLION 1000000000

int main() {

	/* Variables which are den (denominator) and pi. */
	double pi = 0.0, den = 1.0;

	/* For loop will iterate "length" times. If denominator is equal than
	1.0 then divide numerator (4.0) by the denominator (1.0). If not, add
	2 to the denominator and subtract (4/3 which is num/den) from pi. Next,
	add (4/5 or num/den) to pi. */
	int i;
	for(i = 0; i < ONE_BILLION; i++){
		if(den == 1.0){
			pi = NUM / den;
			den += 2;
		}
		else{
			pi = pi - (NUM / den);
			den += 2;
			pi = pi + (NUM / den);
			den += 2;
		}
	}

	printf("The approximation of pi is %.15f\n", pi);

	return 0;
}
