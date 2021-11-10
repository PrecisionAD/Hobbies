#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Node where each class can be stored individially. */
typedef struct Node {
	char class[12];
	struct Node *next;
} node;

/* Just need an instance of this struct to point to 1st node. */
typedef struct list {
	struct list *head;
} list;

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
		printf("Memory allocation failed!\n");
		exit(1);
	}

	return p;
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
	int i = 0;
	char buffer[12];
	char c = ' ';

	printf("Type the name of the class you want to mark as taken\n");
	printf("Class name: ");
	fgets(buffer, 12, stdin);
	
	// Capitalizes the class name in order to compare it later
	while(found == 0) {
		c = buffer[i];
		buffer[i] = toupper(buffer[i]);
		//printf("c = %c\n", c);
		i++;
		if((c - ' ') ==  0) {
			found = 1;
		}
	}
	//printf("new string is %s", buffer);
	
	found = 0;

	// Start comparing from the head and then the body of the list
	do {
		if(strcmp(buffer, prev->class) == 0) {
			head2 = current;
			strcpy(newNode->class, buffer);
			newNode->next = head;
			head = newNode;
			found = 1; //or break instead?
			//break;
			// return node that was found?
		}
		else {
			//printf("buffer = %s", buffer);
			//printf("current class= %s", current->class);
			if(strcmp(buffer, current->class) == 0) {
				puts("in here");
				prev->next = current->next;
				strcpy(newNode->class, buffer);
				newNode->next = head;
				head = newNode;
				found = 1; //or break instead?
				//break;
				//return current node that was found?
			}
		}
		
		prev = prev->next;
		//printf("prev now%s", prev->class);
		current = current->next;
		//printf("current now %s", current->class);
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

	strcpy(newNode->class, course);
	newNode->next = NULL;
	
	/* Point to the correct list to add the new class. */
	if(option == 1) {
		current = head;
	}
	else {
		current = head2;
	}

	if(current == NULL) {
		current = newNode;
	}
	else {
		puts("im here");
		newNode->next = current;
		printf("newNode %s", newNode->class);
		current = newNode;
	}

	if(option == 1) {
		head = current;
	}
	else {
		head2 = current;
	}

}



void removeClass() {

	struct Node *prev;
	struct Node *current;
	int option = 0;
	int found = 0;
	int i = 0;
	char buffer[12];
	char course[12];
	char c = ' ';

	printf("\nWhat's the name of the class you would like to remove?\n");
	printf("Class name: ");
	fgets(course, 12, stdin);
	
	// Capitalize the class name in order to compare it later
	while(found == 0) {
		c = course[i];
		course[i] = toupper(course[i]);
		//printf("c = %c\n", c);
		i++;
		if((c - ' ') ==  0) {
			found = 1;
		}
	}

	//printf("class to remove is %s", course);

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
		found = 0;
		puts("in here now");
		while(current != NULL && found == 0) {
			if(strcmp(current->class, course) == 0) {
				prev->next = current->next;
				printf("\nClass has been removed!\n");
				found = 1;
			}
			prev = prev->next;
			current = current->next;
		}
	}

	if(found != 1) {
		printf("I couldn't find the class %s", course);
	}



}



void editClass() {

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
			editClass();
		}
		else if((option = atoi(buffer)) == 5) {
			done = 1;
		}
		else {
			printf("Wrong option. Try again.\n");
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

	tmp = fopen(fileName, "r+");
	if(tmp == NULL) {
		printf("The file %s could not be found!\n", fileName);
		exit(1);
	}

	return tmp;
}


/* 1. Check that the files exist! 
	 2. Read the taken.txt file and create a list.
	 3. Read the needed.txt file and create a list.
	 4. Show menu to add/move/remove nodes.
	 5. Clean up of pointers. */
int main() {
	
	FILE *file1;
	FILE *file2;
	//struct Node *takenHead = NULL;
	//struct Node *neededHead = NULL;
	char taken[12] = "taken.txt";
	char needed[12] = "needed.txt";

	file1 = checkFile(taken);
	file2 = checkFile(needed);

	//takenHead = 
	createTakenList(file1);
	//neededHead = 
	createNeededList(file2);

	showMenu();

	return 0;
}


