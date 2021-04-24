
/*
 * The intention was to practice with threads to see the
 * difference in computation time. There is also a function
 * that searches and returns the index in which a birthday 
 * appears in pi. There is also 6 threads doing 6 different 
 * things (calculating how many ocurrences of a number appear
 * in pi - the number appears four consecutive times).
 * 
 * The last method (searchBday) will accept a date as a 
 * birthday and the thread assigned to it will search what
 * position in pi that particular ocurrence appears.
 *
 * Author: Adrian Meneses.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define MAX 100000
#define MAX1 10000000
#define MAX3 100000000

int done = 0;


/*
 * Args:
 * 		None.
 *
 * Returns:
 * 		A thread pointer to signal main that it has finished.
 *
 * Notes:
 * 		This funtions along the next 5, do the exact same thing:
 * 		each function is executed by a thread that will search
 * 		for a sequence (4 consecutive numbers together). It will
 * 		also increment a counter to know how many ocurrences it 
 * 		found.
 */
void * searchFives() {

	char dummyBuffer[16];
	FILE *inDummy = NULL;

	inDummy = fopen("billion2.txt", "r");
	if(inDummy == NULL) {
		printf("Could not open the file!\n");
		exit(1);
	}

	// File pointer will read 4 numbers at a time
	fgets(dummyBuffer, 5, inDummy);

	char index0;
	char index1;
	char index2;
	char index3;

	int totalConsecutive = 0;
	int i = 0;
	while(i != MAX3) {
		// Store the next 4 numbers from the file to compare them
		index0 = dummyBuffer[0];
		index1 = dummyBuffer[1];
		index2 = dummyBuffer[2];
		index3 = dummyBuffer[3];

		// Check if the 4 numbers are equal
		if(index0 == '5' && (index0 == index1) && (index0 == index2) && (index0 == index3)) {
			// Increase counter for that consecutive number if equal
			totalConsecutive++;

			// Set *in to point to inDummy
			fgets(dummyBuffer, 5, inDummy);
		}
		// If not equal, advance one number only
		else {
			fseek(inDummy, -3, SEEK_CUR);
			fgets(dummyBuffer, 5, inDummy);
		}
		i++;
	}

	printf("Number 5 appeared %d time in bundles of 4 (5555)\n", totalConsecutive);
	done = 1;

	return NULL;
}//end searchOnes()



void * searchFours() {

	char dummyBuffer[16];
	FILE *inDummy = NULL;

	inDummy = fopen("billion2.txt", "r");
	if(inDummy == NULL) {
		printf("Could not open the file!\n");
		exit(1);
	}

	// File pointer will read 4 numbers at a time
	fgets(dummyBuffer, 5, inDummy);

	char index0;
	char index1;
	char index2;
	char index3;

	int totalConsecutive = 0;
	int i = 0;
	while(i != MAX3) {
		index0 = dummyBuffer[0];
		index1 = dummyBuffer[1];
		index2 = dummyBuffer[2];
		index3 = dummyBuffer[3];

		// Check if the 4 numbers are equal
		if(index0 == '4' && (index0 == index1) && (index0 == index2) && (index0 == index3)) {
			// Increase counter for that consecutive number
			totalConsecutive++;

			// Set *in to point to inDummy
			fgets(dummyBuffer, 5, inDummy);
		}
		// If not equal, advance one number only
		else {
			fseek(inDummy, -3, SEEK_CUR);
			fgets(dummyBuffer, 5, inDummy);
		}
		i++;
	}

	printf("Number 4 appeared %d time in bundles of 4 (4444)\n", totalConsecutive);

	return NULL;

}//end searchOnes()



void * searchThrees() {

	char dummyBuffer[16];
	FILE *inDummy = NULL;

	inDummy = fopen("billion2.txt", "r");
	if(inDummy == NULL) {
		printf("Could not open the file!\n");
		exit(1);
	}

	// File pointer will read 4 numbers at a time
	fgets(dummyBuffer, 5, inDummy);

	char index0;
	char index1;
	char index2;
	char index3;

	int totalConsecutive = 0;
	int i = 0;
	while(i != MAX3) {
		index0 = dummyBuffer[0];
		index1 = dummyBuffer[1];
		index2 = dummyBuffer[2];
		index3 = dummyBuffer[3];

		// Check if the 4 numbers are equal
		if(index0 == '3' && (index0 == index1) && (index0 == index2) && (index0 == index3)) {
			// Increase counter for that consecutive number
			totalConsecutive++;

			// Set *in to point to inDummy
			fgets(dummyBuffer, 5, inDummy);
		}
		// If not equal, advance one number only
		else {
			fseek(inDummy, -3, SEEK_CUR);
			fgets(dummyBuffer, 5, inDummy);
		}
		i++;
	}

	printf("Number 3 appeared %d time in bundles of 4 (3333)\n", totalConsecutive);

	return NULL;

}//end searchOnes()



void * searchTwos() {

	char dummyBuffer[16];
	FILE *inDummy = NULL;

	inDummy = fopen("billion2.txt", "r");
	if(inDummy == NULL) {
		printf("Could not open the file!\n");
		exit(1);
	}

	// File pointer will read 4 numbers at a time
	fgets(dummyBuffer, 5, inDummy);

	char index0;
	char index1;
	char index2;
	char index3;

	int totalConsecutive = 0;
	int i = 0;
	while(i != MAX3) {
		index0 = dummyBuffer[0];
		index1 = dummyBuffer[1];
		index2 = dummyBuffer[2];
		index3 = dummyBuffer[3];

		// Check if the 4 numbers are equal
		if(index0 == '2' && (index0 == index1) && (index0 == index2) && (index0 == index3)) {
			// Increase counter for that consecutive number
			totalConsecutive++;

			// Since we found a sequence, read the next 4 numbers
			fgets(dummyBuffer, 5, inDummy);
		}
		// If not equal, advance one number only
		else {
			fseek(inDummy, -3, SEEK_CUR);
			fgets(dummyBuffer, 5, inDummy);
		}
		i++;
	}

	printf("Number 2 appeared %d time in bundles of 4 (2222)\n", totalConsecutive);

	return NULL;

}//end searchOnes()



void * searchOnes() {

	char dummyBuffer[16];
	FILE *inDummy = NULL;

	inDummy = fopen("billion2.txt", "r");
	if(inDummy == NULL) {
		printf("Could not open the file!\n");
		exit(1);
	}

	// File pointer will read 4 numbers at a time
	fgets(dummyBuffer, 5, inDummy);

	char index0;
	char index1;
	char index2;
	char index3;

	int totalConsecutive = 0;
	int i = 0;
	while(i != MAX3) {
		index0 = dummyBuffer[0];
		index1 = dummyBuffer[1];
		index2 = dummyBuffer[2];
		index3 = dummyBuffer[3];

		// Check if the 4 numbers are equal
		if(index0 == '1' && (index0 == index1) && (index0 == index2) && (index0 == index3)) {
			// Increase counter for that consecutive number
			totalConsecutive++;

			// Set *in to point to inDummy
			fgets(dummyBuffer, 5, inDummy);
		}
		// If not equal, advance one number only
		else {
			fseek(inDummy, -3, SEEK_CUR);
			fgets(dummyBuffer, 5, inDummy);
		}
		i++;
	}

	printf("Number 1 appeared %d time in bundles of 4 (1111)\n", totalConsecutive);

	return NULL;

}//end searchOnes()



void * searchZeros() {

	char dummyBuffer[16];
	FILE *inDummy = NULL;

	inDummy = fopen("billion2.txt", "r");
	if(inDummy == NULL) {
		printf("Could not open the file!\n");
		exit(1);
	}

	// File pointer will read 4 numbers at a time
	fgets(dummyBuffer, 5, inDummy);

	char index0;
	char index1;
	char index2;
	char index3;

	clock_t start = clock();

	int totalConsecutive = 0;
	int i = 0;
	while(i != MAX3) {
		index0 = dummyBuffer[0];
		index1 = dummyBuffer[1];
		index2 = dummyBuffer[2];
		index3 = dummyBuffer[3];

		// Check if the 4 numbers are equal
		if(index0 == '0' && (index0 == index1) && (index0 == index2) && (index0 == index3)) {
			// Increase counter for that consecutive number
			totalConsecutive++;

			// Set *in to point to inDummy
			fgets(dummyBuffer, 5, inDummy);
		}
		// If not equal, advance one number only
		else {
			fseek(inDummy, -3, SEEK_CUR);
			fgets(dummyBuffer, 5, inDummy);
		}
		i++;
	}

	clock_t end = clock();
	clock_t diff = end - start;

	printf("Number 0 appeared %d time in bundles of 4 (0000)\n", totalConsecutive);

	return (void *) diff;

}//end searchOnes()



void * searchBday() {

	char dummyBuffer[16];
	//char key[10] = {'5', '4', '1', '9', '7', '9'};
	char key[10] = {'0', '8', '0', '9', '8', '3'};
	FILE *inDummy = NULL;

	inDummy = fopen("billion2.txt", "r");
	if(inDummy == NULL) {
		printf("Could not open the file!\n");
		exit(1);
	}

	// File pointer will read 4 numbers at a time
	fgets(dummyBuffer, 7, inDummy);
	printf("before while loop dummyBuffer has: %s\n", dummyBuffer);
		
	int n;

	int counter = 0;
	int i = 0;
	while(i != MAX3) {
		n = strcmp(dummyBuffer, key);
		if(n == 0) { 
			break; 
		}
		fseek(inDummy, -5, SEEK_CUR);
		fgets(dummyBuffer, 7, inDummy);
		counter += 1;
		i++;
	}

	printf("Appeared in position %d of Pi \n", counter);
	printf("Found: %s\n", dummyBuffer);

	return NULL;

}//end searchOnes()


/*
 * Args:
 * 		None.
 *
 * Returns:
 * 		Nothing.
 *
 * Notes:
 * 		The idea is to see how fast a program can be when 
 * 		it runs with multiple threads. There are 6 threads 
 * 		that will find how many ocurrences of a sequence for
 * 		a particular number appear in pi.
 */
int main() {

	pthread_t t0;
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;
	pthread_t t5;
	pthread_t B;

	pthread_create(&t0, NULL, searchZeros, NULL);
	pthread_create(&t1, NULL, searchOnes, NULL);
	pthread_create(&t2, NULL, searchTwos, NULL);
	pthread_create(&t3, NULL, searchThrees, NULL);
	pthread_create(&t4, NULL, searchFours, NULL);
	pthread_create(&t5, NULL, searchFives, NULL);
	pthread_create(&B, NULL, searchBday, NULL);


	double diff;
	pthread_join(t0, (void **) &diff);
	printf("diff = %f\n", diff);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	pthread_join(B, NULL);

	return 0;
}
