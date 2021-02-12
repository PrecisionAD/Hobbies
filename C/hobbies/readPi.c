
/*
 * Reading aprox ~340m digits of pi. Reads the ocurrence of
 * every number in pi.
 *
 * Programmed by Adrian Meneses
 * Date: 01/23/2021
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HUND_MILL 100000000
#define TWO_MILL 200000000
#define THREE_MILL 300000000


/*
 * Args:
 * 		None.
 *
 * Returns:
 * 		Nothing.
 *
 * Notes:
 * 		Switch statement will increase the counter 
 * 		for each digit.
 */
void totalDigits() {
	
	char buffer[5];
	FILE *read = NULL;

	read = fopen("billion2.txt", "r");
	if(read == NULL) {
		printf("Error reading the file\n");
		exit(1);
	}

	int enough = 0;
	int zero, one, two, three, four, five, six, seven, eight, nine;
	zero = one = two = three = four = five = six = seven = eight = nine = 0;
	fgets(buffer, 2, read);

	while(enough != THREE_MILL) {
		char c = buffer[0];
		switch(c) {
			case '0': zero++; 	break;
			case '1': one++;		break;
			case '2': two++;		break;
			case '3': three++;	break;
			case '4': four++; 	break;
			case '5': five++; 	break;
			case '6': six++; 		break;
			case '7': seven++; 	break;
			case '8': eight++; 	break;
			case '9': nine++; 	break;
		}

		fgets(buffer, 2, read);
		enough++;
	}

	printf("Total ocurrences are:\n"
				"zero = %d\n"
				"one = %d\n"
				"two = %d\n"
				"three = %d\n"
				"four = %d\n"
				"five = %d\n"
				"six = %d\n"
				"seven = %d\n"
				"eight = %d\n"
				"nine = %d\n"
				, zero, one, two, three, four, five, six, seven, eight, nine);

}

/*
 * args: none.
 *
 * returns: nothing.
 *
 * Notes:
 * 		Main menu.
 */
int main() {

	time_t start = time(NULL);
	totalDigits();
	time_t end = time(NULL);

	time_t diff = end - start;
	printf("\nIt took %ld seconds\n", diff);

	return 0;
}
