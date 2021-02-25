
/*
 * This program opens a file (.srt) that contains the time
 * tags of the dialog of a specific movie or episode. What it 
 * does is adjust the out of sync closed caption by either
 * adding or subtracting an offset entered by the user.
 *
 * As an example, if the closed captions of a movie are behind 
 * half a second (0.5 seconds), the program will ask for a file
 * and then for the amount of offset to add. The program will 
 * then retrieve the digits only from the file (there are 
 * strings as well) and put them into a 2D array. After that,
 * it will adjust the times by adding the 0.5 seconds to the
 * extracted digits and then place them back into the
 * original file but adjusted.
 *
 * Author: Adrian Meneses.
 * v1.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 1000
#define COL 40

void greet();
int addOrSub();
int checkNum(char *key);
FILE * askFile();
void extract(char times[ROW][COL], int len);
void adjust(int *number, int *choice);



/*
 * Args:
 * 		@file contains the file name to be opened.
 * 		@mode contains the mode of how to open the file.
 *
 * Returns:
 * 		A file pointer with the file requested.
 *
 * Notes:
 * 		This function was made to eliminate the duplicate code
 * 		that was in various functions to open files on the fly.
 */
FILE * openFile(char *file, char *mode) {

	FILE *fp;

	fp = fopen(file, mode);
	if(fp == NULL) {
		printf("The file could not be opened! Check the name!\n");
		exit(1);
	}

	return fp;
}


/*
 * Args:
 * 		None.
 *
 * Returns:
 * 		Nothing.
 *
 * Notes:
 * 		Part of the main() is to prompt the user to enter a file and a number
 * 		(either add or subtract) to fix the sync in the .srt file. After
 * 		asking for the file, it will add all divide every line in the file
 * 		in half and store it into a 2D array. Later, it will call the function
 * 		extract() which will get rid of the chars and strings to leave a 
 * 		sequence of only numbers such as 000008712 for example.
 *
 * 		Then, it will add/subtract the offset. Finally, it will add leading
 * 		zeros (since the left most zeros are omitted by the language C) and
 * 		place the adjusted number back in the file.
 */
int main(int argc, char *argv[]) {

	// Display how program works
	greet();
	
	// Ask if addition of subtraction is needed
	int answer = addOrSub();

	char key[20];
	printf("\nEnter the time you want to adjust:\n");
	printf("Time: ");
	fgets(key, 20, stdin);

	// Ask for time to subtract and check the number is valid
	int offset = checkNum(key);

	// Ask for the file and check if it exists or is not NULL
	FILE *readFile = askFile();

	char buffer[100];
	char times[ROW][COL];
	char *token;
	int row = 0;

	// Read each line from the file.txt and put it into the array times[]
	while(fgets(buffer, 100, readFile) != NULL) {
		token = strtok(buffer, "");
		strcpy(times[row++], token);
	}

	// Extract the digits only from each line in the file
	extract(times, row);

	// Adjust the requested time
	adjust(&offset, &answer);

	// Close the file pointer
	fclose(readFile);

	// Delete the extracted.txt file
	remove("extracted.txt");

	return  0;

} //end main

/* 
 * Args:
 * 		None.
 *
 * Returns:
 * 		Nothing.
 *
 * Notes:
 * 		The greet() will explain how to enter values to add 
 * 		or subtract.
 */
void greet() {

	puts("If file contains two decimals:");
	printf("To subtract 10 seconds, enter 1000\n"
			"To subtract 1 second, enter 100\n"
			"To subtract 0.5 seconds, enter 50\n\n");

	puts("If file contains three decimals:");
	printf("To subtract 10 seconds, enter 10000\n"
			"To subtract 1 second, enter 1000\n"
			"To subtract 0.5 seconds, enter 500\n\n");
	
}


/*
 * Args:
 * 		None.
 *
 * Returns:
 * 		The option selected by the user. It could be the number
 * 		1 (to add some offset) or number 2 (to subtract some offset).
 */
int addOrSub() {

	char choice[5];
	puts("Press 1 if you need addition or 2 if you need subtraction.");
	printf("Choice: ");
	fgets(choice, 10, stdin);
	int number = atoi(choice);

	return number;
}


/*
 * Args:
 * 		@key contains the number (offset) to be converted.
 *
 * Returns:
 * 		A valid number (offset).
 *
 * Notes:
 * 		The key() will check that the value entered to subtract is a positive number.
 */
int checkNum(char *key) {

	int number = atoi(key);
	if(number <= 0) {
		do {
			puts("You need to enter a number higher than 0.");
			printf("Enter the time you want to adjust:\n");
			printf("Number: ");
			fgets(key, 5, stdin);
			number = atoi(key);
		} while(number <= 0);
	}
	return number;
}


/* 
 * Args:
 * 		None.
 *
 * Returns:
 * 		A file pointer with the new file to read from.
 *
 * Notes:
 * 		The askFile() will attempt to open the file specified by the user. If the file does not
 * 		exist, the program will exit.
 */
FILE * askFile() {

	char file[20];
	char test[50];
	printf("\nEnter the name of the file, for example, \"file.txt\"\n");
	printf("File: ");
	fgets(file, 20, stdin);
	file[strlen(file)-1] = '\0';
	strcpy(test, "/Users/itoyan/Documents/C/sync/");
	strcat(test, file);


	FILE *readFile;
	readFile = openFile(file, "r");
	// Set up
	/*FILE *readFile;
	readFile = fopen(file, "r");
	if(readFile == NULL) {
		printf("\nFile could not be located/opened! Check the name of the file again.\n");
		exit(1);
	}*/
	return readFile;
}


/* 
 * Args:
 * 		@times contains all the numbers and chars to be extracted.
 * 		@len contains how big the array is.
 *
 * Returns:
 * 		Does not return anything but creates a file with the extracted
 * 		numbers.
 *
 * Notes:
 * 		The extract() will receive a 2D array (times) pre-filled with all 
 * 		the times from a .srt file and will extract only the digits to 
 * 		subtract the required time to sync into the extracted array.
 */
void extract(char times[ROW][COL], int len) {

	int space = 0;
	int row = 0;
	int col = 0;
	int index = 0;
	FILE *fp = fopen("extracted.txt", "a");

	for(row = 0; row < len; row++) {
		for(col = 0; col < strlen(times[row]); col++) {
			char c = times[row][col];
			switch(c) {
				case ' ':	space++;
							if(space == 2) { fprintf(fp, "%s", "\n"); }
							break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':	fprintf(fp, "%c", c);
							break;
				default:
							index++;
			}
		}//end inner for loop
		fprintf(fp, "%s", "\n");
		space = 0;
		//break;
	}//end outer for loop
	fclose(fp);
}


/* 
 * Args:
 *		@offset contains the 'time' to be added or subtracted
 *		@choice contains the option to make the addition or subtraction
 *
 * Returns:
 * 		Nothing.
 *
 * Notes:
 * 		The adjust() will recieve a key(offset) to subtract to each
 * 		extracted number from the original file and placed in a file 
 * 		named 'adjusted'. Choice will contain either 1 if addition is
 * 		needed or 2 if subtraction is needed.
 *
 *		We start by getting the contents from the file, then we 
 *		eliminate the '\n' at the end to avoid issues. We then 
 *		compute the length for each line in the file to know how 
 *		many zeros to add to the left of the number later (if any).
 */
void adjust(int *offset, int *choice) {

	FILE *fp = fopen("extracted.txt", "r");
	FILE *fp2 = fopen("fixed.txt", "a");
	char buffer[15];
	char adjusted[15];
	char *token;
	int num = 0;

	while(fgets(buffer, 15, fp) != NULL) {
		token = strtok(buffer, "");						// Get content from buffer
		buffer[strlen(buffer)-1] = '\0';			// Get rid of '\n' at the end
		int originalLen = strlen(buffer);			// Get original length to place zeros back

		num = atoi(token);
		if(*choice == 1) {
			num = num + *offset;
		}
		else {
			num = num - *offset;
		}
		sprintf(adjusted, "%d", num);
		
		/* Here, this is what happens: if the number before adjustment 
		 * is say '9112556' and after adding the offset it becomes
		 * '10112556' then we know that the difference is 1 in length
		 * between the two. That means that we need to add one zero to
		 * the left of the adjusted number.
		 */ 
		int modLen = strlen(adjusted);						// Get length after adjusted times
		int adjustedLen = originalLen - modLen;		// Get difference in length
		
		if(adjustedLen > 0) {											// If difference greater than 0, add the zeros
			do {
				fprintf(fp2, "%s", "0");
				adjustedLen--;
			} while(adjustedLen > 0);
		}
		
		fprintf(fp2, "%s", adjusted);
		fprintf(fp2, "%s", "\n");
	}
	fclose(fp);
	fclose(fp2);

}



