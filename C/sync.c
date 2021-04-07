#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extract(char times[1200][50], char extracted[1200][50], int len);


int main(int argc, char *argv[]) {

	puts("If file conatins two decimals:");
	printf("To subtract 10 seconds, enter 1000\n"
			"To subtract 1 second, enter 100\n"
			"To subtract 0.5 seconds, enter 50\n\n");

	puts("If file contains three decimals:");
	printf("To subtract 10 seconds, enter 10000\n"
			"To subtract 1 second, enter 1000\n"
			"To subtract 0.5 seconds, enter 500\n\n");
	
	char key[5];
	printf("Enter the time you want to subtract:\n");
	printf("Time: ");
	fgets(key, 5, stdin);

	// Ask for time to subtract
	int number = atoi(key);
	if(number <= 0) {
		do {
			puts("You need to enter a number higher than 0.");
			printf("Enter the time you want to subtract:\n");
			printf("Number: ");
			fgets(key, 5, stdin);
			number = atoi(key);
		} while(number <= 0);
	}

	// Ask for the file 
	char file[20];
	//char test[50];
	printf("\nEnter the name of the file, for example, \"file.txt\"\n");
	printf("File: ");
	fgets(file, 20, stdin);
	file[strlen(file)-1] = '\0';
	//strcpy(test, "/Users/itoyan/Documents/C");
	//strcat(test, file);


	// Set up
	FILE *readFile;
	int done = 0;
	readFile = fopen(file, "r");
	if(readFile == NULL) {
		printf("\nFile could not be located/opened! Check the name of the file again.\n");
		do {
			readFile = fopen(file, "r");
			if(readFile == NULL) {
				printf("\nFile could not be located/opened! Check the name of the file again.\n");
				printf("Enter file: ");
				fgets(file, 20, stdin);
				file[strlen(file) -1] = '\0';
			}
			else {
				done = 1;
			}
		} while(done != 0);
	}
	//printf("file is %s\n", file);
	//printf("len of file is %lu\n", strlen(file));
	/*do {
		readFile = fopen(file, "r");
		if(readFile == NULL) {
			printf("\nFile could not be located/opened! Check the name of the file again.\n");
			printf("Enter file: ");
			fgets(file, 20, stdin);
			//file[strlen(file) -1] = '\0';
		}
		else {
			done = 1;
		}
	} while(done != 0);*/

	char buffer[100];
	char times[1200][50];
	char extracted[1200][50];
	char *token;
	int row = 0;

	while(fgets(buffer, 100, readFile) != NULL) {
		token = strtok(buffer, "");
		strcpy(times[row++], token);
	}
	
	fclose(readFile);

	// Extract the digits only from each line in the file
	extract(times, extracted, row);

	printf("original row[0]: %s\n", times[0]);
	//printf("original row[1]: %s\n", times[1]);
	printf("after extraction[0]: %s\n", extracted[0]);
	//printf("after extraction[1]: %s\n", extracted[1]);




	return  0;
}

/* The extract() will receive a 2D array pre-filled with all the times from a .srt file
 * and will extract only the digits to subtract the required time to sync. */
void extract(char times[1200][50], char extracted[1200][50], int length) {


	// Arrays to hold the extracted numbers from a single line
	char trimLeft[50];
	char trimRight[50];
	trimLeft[0] = '\0';
	trimRight[0] = '\0';

	int spaces = 0;
	int row = 0;
	int col = 0;
	int len = 0;

	//printf("length of times is: %d\n", length);

	for(row = 0; row < 2; row++) {
		//printf("len is: %lu\n", strlen(times[row]));
		//printf("row: %d\n", row);
		len = strlen(times[row]) -1;
		//printf("working on %s\n", times[row]);
		for(col = 0; col < strlen(times[row]); col++) {
			//printf("times[1] %s\n", times[1]);
			times[row][len] = '\0';
			//printf("spaces is: %d\n", spaces);
			//c  = times[row][col];
			char t = times[row][col];
			//printf("t is: %c\n", t);
			if((t - ' ') == 0) {
				spaces++;
				//puts("space increased");
			}
			else if(((t - ':') == 0) || ((t - ',') == 0) || ((t - '-') == 0) || ((t - '>') == 0))  {
				//strcat(arrows, &t);
				//printf("---arrows: %s\n", arrows);
			}
			else if(spaces == 0) {
				//puts("numL");
				strcat(trimLeft, &t);
				//printf("trimLeft: %s\n", trimLeft);
			}
			else if(spaces == 2) {
				//puts("numR");
				strcat(trimRight, &t);
				//printf("trimRight: %s\n", trimRight);
			}
		}
		strcpy(*(extracted + row), trimLeft);
		strcat(*(extracted + row), " ");
		strcat(*(extracted + row), trimRight);
		//printf("trimLeft: %s\n", trimLeft);
		//printf("trimRight: %s\n", trimRight);
		spaces = 0;
		trimLeft[0] = '\0';
		trimRight[0] = '\0';
	}
}
