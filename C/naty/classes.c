#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */


/* Node where each class can be stored individially. */
typedef struct Node {
	char class[12];
	struct Node *next;
} node;

/* These are the head pointers to the corresponding list of classes. */
struct Node *head = NULL;
struct Node *head2 = NULL;


/*
 * args:
 * 	@size: contains the value for the memory allocation
 *
 * returns:
 * 	The newly created memory allocation
 */
void * dmalloc(size_t size) {
	
	void *p = malloc(size);
	if(p == NULL) {
		printf(BOLDMAGENTA "Memory allocation failed!\n" RESET);
		exit(1);
	}

	return p;
}


/*
 *
 */
void freeMemory() {
	
	node *tmp = head;

	while(head != NULL) {
		head = head->next;
		free(tmp);
		tmp = head;
	}

	tmp = head2;
	
	while(head2 != NULL) {
		head2 = head2->next;
		free(tmp);
		tmp = head2;
	}
}


/*
 * args:
 * 	@*word: is the name of the word to capitalize
 * 	@*buffer: where the capitalized word will be saved
 *
 * Returns:
 * 	A char pointer (buffer) with the newly capitalized
 * 	word.
 *
 * Notes:
 * 	Here we get a word in the format 'className classNumber'
 * 	that needs capitalization. The loop will capitalize the
 * 	letters until a space is found.
 */
char * capitalize(char *word, char *buffer) {

	int found = 0;
	int i = 0;
	char c = ' ';

	// First we copy the word to the buffer before comparison
	strcpy(buffer, word);

	while(found == 0) {
		c = buffer[i];
		buffer[i] = toupper(buffer[i]);
		i++;
		if((c - ' ') ==  0) {
			found = 1;
		}
	}

	return buffer;
}


/*
 * Save the changes (if any) that were made to either list to the
 * same files.
 */
void saveChanges() {
	
	FILE *fp1;
	FILE *fp2;
	node *current = head;
	node *current2 = head2;
	char buffer[12];

	fp1 = fopen("taken.txt", "w");
	fp2 = fopen("needed.txt", "w");

	while(current != NULL) {
		strcpy(buffer, current->class);
		fprintf(fp1, "%s", buffer);
		current = current->next;
	}

	while(current2 != NULL) {
		strcpy(buffer, current2->class);
		fprintf(fp2, "%s", buffer);
		current2 = current2->next;
	}

	fclose(fp1);
	fclose(fp2);
}



/*
 * Marks a class (deletes it) from the needed list and places 
 * it (adds it) in the taken list.
 */
void markClass() {
	
	struct Node *prev = head2;
	struct Node *current = head2->next;
	struct Node *newNode = dmalloc(sizeof(node));
	int found = 0;
	char buffer[12];
	char course[12];

	printf("Type the name of the class you want to mark as taken\n");
	printf("Class name: ");
	fgets(course, 12, stdin);
	
	// Capitalizes the class name in order to compare it later
	capitalize(course, buffer);
	
	found = 0;

	// Start comparing from the head and then the body of the list
	do {
		if(strcmp(buffer, prev->class) == 0) {
			head2 = current;
			strcpy(newNode->class, buffer);
			newNode->next = head;
			head = newNode;
			found = 1; 
		}
		else {
			if(strcmp(buffer, current->class) == 0) {
				puts("in here");
				prev->next = current->next;
				strcpy(newNode->class, buffer);
				newNode->next = head;
				head = newNode;
				found = 1; 
			}
		}
		
		prev = prev->next;
		current = current->next;
	} while(found == 0 && current != NULL);

}


/*
 * args:
 * 	@option: signals which list the class goes to
 * 	@course: the name of the class to add
 *
 * returns:
 * 	Nothing.
 *
 * Notes:
 * 	Simply adds a class to the selected list.
 */
void addClass(int option, char *course) {

	struct Node *newNode = dmalloc(sizeof(node));
	struct Node *current;
	char buffer[12];
	
	strcpy(newNode->class, capitalize(course, buffer));
	newNode->next = NULL;
	
	/* Point to the correct list to add the new class. */
	if(option == 1) {
		current = head;
	}
	else {
		current = head2;
	}

	// Check where to add the new node, head or body of list
	if(current == NULL) {
		current = newNode;
	}
	else {
		newNode->next = current;
		current = newNode;
	}

	if(option == 1) {
		head = current;
	}
	else {
		head2 = current;
	}

}


/*
 * args:
 * 	None.
 *
 * Returns:
 * 	Nothing.
 *
 * Notes:
 * 	Removes a class from either list. First we capitalize
 * 	the class name because every single class name from 
 * 	either list is already capitalized. This is so we can
 * 	compare when removing the nodes.
 */
void removeClass() {

	struct Node *prev;
	struct Node *current;
	int option = 0;
	int found = 0;
	char buffer[12];
	char course[12];

	printf("\nWhat's the name of the class you would like to remove?\n");
	printf("Class name: ");
	fgets(course, 12, stdin);
	
	// Capitalize the class name in order to compare it later
	strcpy(course, capitalize(course, buffer));

	printf("\nOn which list you want to delete the class?\n"
				 "1. Already taken list\n"
				 "2. Needed classes list\n");
	printf("Option: ");
	fgets(buffer, 12, stdin);
	option = atoi(buffer);

	// Sets the temp pointers to the relevant list
	if(option == 1) {
		prev = head;
		current = head->next;
	}
	else {
		prev = head2;
		current = head2->next;
	}

	// Search stars at the head and then the body of the list
	if(strcmp(prev->class, course) == 0) {
		if(option == 1) {
			head = current;
		}
		else {
			head2 = current;
		}
	}
	else {
		found = 0; // Reset and reuse it as a boolean
		while(current != NULL && found == 0) {
			if(strcmp(current->class, course) == 0) {
				prev->next = current->next;
				printf(BOLDGREEN "\nClass has been removed!\n" RESET);
				found = 1;
			}
			prev = prev->next;
			current = current->next;
		}
	}

	if(found != 1) {
		printf(BOLDMAGENTA "\nCould you check the name again? I couldn't find the class %s" RESET, course);
	}
}


void prepareClass() {

	int option = 0;
	char course[12];
	char buffer[12];

	printf("\nWhat's the name of the class you would like to add?\n");
	printf("Class name: ");
	fgets(course, 12, stdin);

	printf("\nOn which list you want to add the class?\n"
				 "1. Already taken list\n"
				 "2. Needed classes list\n");
	printf("Option: ");
	fgets(buffer, 12, stdin);
	option = atoi(buffer);

	addClass(option, course);
}


/*
 * Prints both lists side by side for better viewing.
 */
void printLists() {

	struct Node *tmp1 = head;
	struct Node *tmp2 = head2;
	int done = 0;
	int done1 = 0;
	int done2 = 0;

	/* We start printing the nodes from each list side by side
	 * until a list has no more nodes to print. If that is the 
	 * case, it means only one list has remaining nodes which
	 * in turn it means that the other list has printed all of
	 * its nodes.
	 */
	printf("\nClasses already taken:		   Classes needed:\n");
	while(done == 0) {
		if(tmp1 != NULL && tmp2 != NULL) {
			tmp1->class[strlen(tmp1->class) -1] = '\0';
			tmp2->class[strlen(tmp2->class) -1] = '\0';
			printf("┌------------------┐             ┌------------------┐\n");
			printf("|%13s     |             |%13s     |\n",tmp1->class, tmp2->class);
			printf("└------------------┘             └------------------┘\n");
			tmp1->class[strlen(tmp1->class)] = '\n';
			tmp2->class[strlen(tmp2->class)] = '\n';
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}

		if(tmp1 == NULL || tmp2 == NULL) {
			done = 1;
		}
	}

	// If we are here either list (temp1 or temp2) will print
	while(done1 == 0) {
		if(tmp1 != NULL) {
			tmp1->class[strlen(tmp1->class) -1] = '\0';
			printf("┌------------------┐\n");
			printf("|%13s     |         \n",tmp1->class);
			printf("└------------------┘\n");
			tmp1->class[strlen(tmp1->class)] = '\n';
			tmp1 = tmp1->next;
		}

		if(tmp1 == NULL) {
			done1 = 1;
		}
	}

	while(done2 == 0) {
		if(tmp2 != NULL) {
			tmp2->class[strlen(tmp2->class) -1] = '\0';
			printf("                                 ┌------------------┐\n");
			printf("                                 |%13s     |         \n",tmp2->class);
			printf("                                 └------------------┘\n");
			tmp2->class[strlen(tmp2->class)] = '\n';
			tmp2 = tmp2->next;
		}

		if(tmp2 == NULL) {
			done2 = 1;
		}
	}

}


/*
 * Show the menu options to the user and call the
 * relevant functions to perform the actions.
 */
void showMenu() {

	char buffer[4];
	int option = 0;
	int done = 0;

	do {
		printf("\nMain Menu\n");
		printf("1. Mark a class as taken \n");
		printf("2. Add a class\n");
		printf("3. Remove a class\n");
		printf("4. Print the lists\n");
		printf("5. Exit!\n\n");
		printf("Select an option from the menu: ");
		fgets(buffer, 3, stdin);

		if((option = atoi(buffer)) == 1) {
			printLists();
			markClass();
		}
		else if((option = atoi(buffer)) == 2) {
			printLists();
			prepareClass();
		}
		else if((option = atoi(buffer)) == 3) {
			printLists();
			removeClass();
		}
		else if((option = atoi(buffer)) == 4) {
			printLists();
		}
		else if((option = atoi(buffer)) == 5) {
			done = 1;
		}
		else {
			printf(BOLDMAGENTA "Wrong option. Try again.\n" RESET);
		}
		
	} while(done == 0);
	
}


/*
 * args:
 * 	@*file: the file pointer needed to create a list
 *
 * returns:
 * 	A pointer to the list of needed classes.
 *
 * This will create the nodes (list) of classes.
 *
 */
struct Node * createNeededList(FILE *file) {

	struct Node *newNode;
	char buffer[12];

	/* We create the list of classes here.
	 * Allocate memory for the new node, copy
	 * the data, and get rid of the newline 
	 * character to prevent formatting issues
	 * when printing the list. */
	while(fgets(buffer, 12, file) != NULL) {
		newNode = malloc(sizeof(struct Node));
		strcpy(newNode->class, buffer);
		newNode->next = NULL;
		buffer[strlen(buffer) -1] = '\0';

		if(head2 == NULL) {
			head2 = newNode;
		}
		else {
			struct Node *tmp = head2;

			while(tmp->next != NULL) {
				tmp = tmp->next;
			}

			tmp->next = newNode;
		}
	}

	/* Return a head pointer of the list created. */
	return head2;
}


/*
 * args:
 * 	@*file: the file pointer needed to create a list
 *
 * returns:
 * 	A pointer to the list of taken classes.
 *
 * This will create the nodes (list) of classes.
 *
 */
struct Node * createTakenList(FILE *file) {

	struct Node *newNode;
	char buffer[12];

	/* We create the list of classes here.
	 * Allocate memory for the new node, copy
	 * the data, and get rid of the newline 
	 * character to prevent formatting issues
	 * when printing the list. */
	while(fgets(buffer, 12, file) != NULL) {
		newNode = malloc(sizeof(struct Node));
		strcpy(newNode->class, buffer);
		newNode->next = NULL;
		buffer[strlen(buffer) -1] = '\0';

		if(head == NULL) {
			head = newNode;
		}
		else {
			struct Node *tmp = head;

			while(tmp->next != NULL) {
				tmp = tmp->next;
			}

			tmp->next = newNode;
		}
	}

	/* Return a head pointer of the list created. */
	return head;
}

/*
 * args:
 * 	@*fileName: name of the file to open
 *
 * returns:
 *	A FILE pointer with the newly opened file.
 */
FILE * checkFile(char * fileName) {

	FILE *tmp;

	tmp = fopen(fileName, "r");
	if(tmp == NULL) {
		printf("The file %s could not be found!\n", fileName);
		exit(1);
	}

	return tmp;
}


/*
 * We start by first checking that the files 
 * exist. Then, we read each file and create 
 * a linked list for later use.
 */
int main() {
	
	FILE *file1;
	FILE *file2;
	char taken[12] = "taken.txt";
	char needed[12] = "needed.txt";

	file1 = checkFile(taken);
	file2 = checkFile(needed);

	createTakenList(file1);
	createNeededList(file2);

	fclose(file1);
	fclose(file2);

	// Do the computations needed by the user
	showMenu();

	// All done, we now save the chages to the file
	saveChanges();
	
	// Now is time to do some clean-up
	freeMemory();

	return 0;
}


