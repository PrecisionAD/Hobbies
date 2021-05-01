
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
#define ONE_BILLION 1000000000000

int main() {

	double i;
	int flag = 0;
	double pi = 4;
	
	for(i = 3; i < 20000000000; i += 2) {
		if(flag) {
			pi += 4.0 / i;
		}
		else {
			pi -= 4.0 / i;
		}

		flag = !flag;
	}

	printf("The approximation of pi is %.25f\n", pi);

	return 0;

}

