#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


void updateNeededList(struct Node *takenList, struct Node *neededList) {
	puts("hello");
	struct Node *tmp1 = takenList;

	puts("Current classes Needed:");
	while(tmp1 != NULL) {
		printf("┌------------------┐\n");
		printf("|%s",tmp1->class);
		printf("└------------------┘\n");
		tmp1 = tmp1->next;
	}


}



void showMenu(struct Node *takenList, struct Node *neededList) {

	printf("Select an option from the menu\n");
	printf("1. Mark a class as taken \n");
	printf("2.\n");
	printf("3.\n");
	printf("4.\n\n");

	char buffer[4];
	int option = 0;

	printf("option: ");
	fgets(buffer, 3, stdin);
	if((option = atoi(buffer)) == 1) {
		updateNeededList(takenList, neededList);
	}

}


/*
 * args:
 * 	- className: the name of the current class to add
 *
 * returns:
 * 	A pointer to the list of taken classes.
 *
 * This will create the nodes (list) of the
 * classes that have been taken already.
 *
 */
struct Node * createNeededList(char *className) {

	struct Node *newNode;

	newNode = malloc(sizeof(struct Node));

	strcpy(newNode->class, className);
	//printf("im here and the class is %s\n", newNode->class);

	if(head2 == NULL) {
		head2 = newNode;
	}
	else {
		struct Node *tmp = head2;

		while(tmp->next != NULL) {
			tmp = tmp->next;
		}

		//printf("Node %s", newNode->class);
		tmp->next = newNode;
	}

	return head2;
}


/*
 * args:
 * 	- className: the name of the current class to add
 *
 * returns:
 * 	A pointer to the list of taken classes.
 *
 * This will create the nodes (list) of the
 * classes that have been taken already.
 *
 */
struct Node * createTakenList(FILE *file1) {

	struct Node *newNode;
	char buffer[12];

	while(fgets(buffer, 12, file1) != NULL) {
		newNode = malloc(sizeof(struct Node));
		strcpy(newNode->class, buffer);
		newNode->next = NULL;
		if(head == NULL) {
			head = newNode;
		}
		else {
			struct Node *tmp = head;
			puts("--2--");

			while(tmp->next != NULL) {
				puts("--3--");
				tmp = tmp->next;
			}

			//printf("Node %s", newNode->class);
			tmp->next = newNode;
		}
	}

	return head;
}


FILE * checkFile(char * fileName) {

	FILE *tmp;

	tmp = fopen(fileName, "r");
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
	struct Node *takenHead = NULL;
	struct Node *neededHead = NULL;
	char taken[12] = "taken.txt";
	char needed[12] = "needed.txt";
	char buffer[12];

	file1 = checkFile(taken);
	file2 = checkFile(needed);

	puts("--1--");
	takenHead = createTakenList(file1);

	puts("--1--");

	while(fgets(buffer, 12, file2) != NULL) {
		//printf("%s", buffer);
		neededHead = createNeededList(buffer);
	}

	showMenu(takenHead, neededHead);

	/*struct Node *tmp = takenHead;

	while(tmp->next != NULL) {
		tmp = tmp->next;
	}

	printf("last node is %s\n", tmp->class);*/

	return 0;
}


