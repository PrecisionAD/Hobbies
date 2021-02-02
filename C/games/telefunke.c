/*
 * Record keeping program. It will open a file (scores.txt)
 * and start saving the current points for the round for each
 * player. As of right now, up to 6 players can play.
 *
 * Programmer: Adrian Meneses
 * Date: 01/15/2021
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIX 6
#define MAX_NAME 15 

int row = 0;
int gameRound = 0;
int totalScore[SIX][5] = { {0}, {0}, {0}, {0}, {0}, {0} };

void printDone() {
	
	printf("\n\n\n****************\n");
	printf("* FINAL SCORES *\n");
	printf("****************");

}

/*
 * args: none.
 *
 * returns: nothing.
 *
 * Notes:
 * 		Print everything that was saved to the file 
 * 		for each player.
 */ 		
void printFile() {

	char buffer[100];
	FILE *fp = NULL;

	fp = fopen("scores.txt", "r");
	if(fp == NULL) {
		printf("scores.txt could not be openend!\n");
		exit(1);
	}

	while(fgets(buffer, 100, fp) != NULL) {
		printf("%s", buffer);
	}

	fclose(fp);

}


/* args: none.
 *
 * returns: nothing.
 *
 * Notes:
 * 		This will add to the end of the table the total 
 * 		scores print out for each player.
 */ 		
void updateFile() {

	int i;
	FILE *fp = NULL;

	fp = fopen("scores.txt", "a");
	if(fp == NULL) {
		printf("scores.txt could not be openend!\n");
		exit(1);
	}

	for(i = 0; i < SIX; i++) {
		fprintf(fp, "| %-7d", totalScore[i][0]);
	}

	fprintf(fp, "%s", "|Total Scores");
	fprintf(fp, "%s", "\n└--------┴--------┴--------┴--------┴--------┴--------┘\n");

	fclose(fp);

}


/*
 * args: none.
 *
 * returns: nothing.
 *
 * Notes:
 * 		Prints the table for the current game and adds the 
 * 		current total score for each player at the end.
 */
void printTable() {

	char buffer[100];
	FILE *fp = NULL;
	int i;

	fp = fopen("scores.txt", "r");
	if(fp == NULL) {
		printf("scores.txt could not be openend!\n");
		exit(1);
	}

	while(fgets(buffer, 100, fp) != NULL) {
		printf("%s", buffer);
	}
	
	for(i = 0; i < SIX; i++) {
		printf("| %-7d", totalScore[i][0]);
	}

	puts("|Current Total");
	printf("%s", "└--------┴--------┴--------┴--------┴--------┴--------┘\n");

	fclose(fp);

}


/*
 * args: @players contains the names of the players.
 *
 * returns: nothing.
 *
 * Notes:
 * 		This will save to the file the header of the table 
 * 		with the names of each player. This fucntion is
 * 		only run once everytime in the program.
 */
void writeFile(char players[][MAX_NAME]) {

	int i;
	FILE *fp = NULL;

	fp = fopen("scores.txt", "a");
	if(fp == NULL) {
		printf("scores.txt could not be openend!\n");
		exit(1);
	}

	fprintf(fp, "%s", "\n\n┌--------┐\n");
	fprintf(fp, "%s", "| TABLE  | \n");
	fprintf(fp, "%s", "├--------┼--------┬--------┬--------┬--------┬--------┐\n");

	/* Save players name's to the file. */
	for(i = 0; i < SIX; i++) {
		fprintf(fp, "%c %-7s", '|', players[i]);
	}
	
	fprintf(fp, "%s", "|");
	fprintf(fp, "%s", "\n├--------┼--------┼--------┼--------┼--------┼--------┤\n");

	fclose(fp);

}


/*
 * args: none.
 *
 * returns: nothing.
 *
 * Notes:
 * 		Simply prints the dividers for each cell in the table.
 */
void printDividers() {

	FILE *fp = NULL;

	fp = fopen("scores.txt", "a");
	if(fp == NULL) {
		printf("scores.txt could not be openend!\n");
		exit(1);
	}

	fprintf(fp, "%s", "\n├--------┼--------┼--------┼--------┼--------┼--------┤\n");

	fclose(fp);

}



/*
 * args:
 *
 * returns:
 *
 * Notes:
 *
 */
void printPlayers(int *selected, char players[][MAX_NAME]) {

	if(selected[0] != 1) { printf("1) %s\n", players[0]); }
	else { printf("1) %s ✓\n", players[0]); }

	if(selected[1] != 1) { printf("2) %s\n", players[1]); }
	else { printf("2) %s ✓\n", players[1]); }

	if(selected[2] != 1) { printf("3) %s\n", players[2]); }
	else { printf("3) %s ✓\n", players[2]); }
		
	if(selected[3] != 1) { printf("4) %s\n", players[3]); }
	else { printf("4) %s ✓\n", players[3]); }
		
	if(selected[4] != 1) { printf("5) %s\n", players[4]); }
	else { printf("5) %s ✓\n", players[4]); }
		
	if(selected[5] != 1) { printf("6) %s\n", players[5]); }
	else { printf("6) %s ✓\n", players[5]); }

	puts("");
}


void enterScores(char players[][MAX_NAME], int *totalScores, char game[][MAX_NAME]) {

	int allDone = 0;
	int points = 0;
	int selectedOption = 0;
	int selected[6] = { 0, 0, 0, 0, 0, 0 };
	char option[6];
	char buffer[5];
	int done = 0;

	printf("╔═════════╗\n");
	printf("║ %-6s  ║ <=== Game you are currently playing!\n", game[gameRound++]);
	printf("╚═════════╝\n");
	
	while(done != 1) {
		printf("\nUpdate score for which player?\n");

		// If name has not been updated, print it
		printPlayers(selected, players);

		// Ask for option and convert it to number
		printf("Enter option: ");
		fgets(option, 3, stdin);	
		selectedOption = atoi(option);

		// Check if player was updated already
		if(selected[selectedOption - 1] == 0) {
			printf("Enter new score for %s: ", players[selectedOption - 1]);
			fgets(option, 6, stdin);
			points = atoi(option);
			
			totalScores[selectedOption - 1] += points;
			selected[selectedOption - 1] = 1; // Mark player as updated
			allDone++;
			
			printf("Is the score correct?");
			fgets(buffer, 5, stdin);
			if(strcmp(buffer, "no\n") == 0 || strcmp(buffer, "n\n") == 0) {
				totalScores[selectedOption - 1] -= points;
				selected[selectedOption - 1] = 0;
				allDone--;
				puts("");
			}
		}

		// If all players updated, move on
		if(allDone == 6) { done = 1; }

	}
}




/*
 * args: @players contains the names of the players.
 * 			 @totalScores contains the scores for the players.
 * 			 @game contains the round type currently in play.
 *
 * returns: nothing.
 *
 * Notes:
 * 		This will ask to enter the points obtained for each
 * 		player in the round. If a mistakes was made while
 * 		entering a score, the option to redo it is present.
 */
void setScores(char players[][MAX_NAME], int *totalScores, char game[][MAX_NAME]) {

	//int i = 0;
	//int temp = 0;
	//int counter = 0;
	//char buffer[SIX];
	//char tempScore[SIX];
	//char tempTotal[SIX];

	printf("╔═════════╗\n");
	printf("║ %-6s  ║ <=== Game you are currently playing!\n", game[gameRound++]);
	printf("╚═════════╝\n");
	
	//enterScores(players, totalScores);
	puts("");

}


/*
 * args: @players contains the names of the players.
 * 			 @totalScores contains the scores for the players.
 * 			 @game contains the round type currently in play.
 * 
 * returns: nothing.
 *
 * Notes:
 * 		This will save the points obtained by each player in a 
 * 		new row in the table.
 */
void saveScores(char players[][MAX_NAME], int *currentScore, char game[][MAX_NAME]) {

	int i;
	FILE *fp = NULL;

	fp = fopen("scores.txt", "a");
	if(fp == NULL) {
		printf("scores.txt could not be openend!\n");
		exit(1);
	}

	/* Loop to update the scores. */
	for(i = 0; i < SIX; i++) {
		fprintf(fp, "| %-7d", currentScore[i]);
		totalScore[i][0] = (currentScore[i] + totalScore[i][0]);
		currentScore[i] = 0;
	}
	
	fprintf(fp, "%s", "|");
	fprintf(fp, "%s", game[row++]);
	fprintf(fp, "%s", "\n├--------┼--------┼--------┼--------┼--------┼--------┤\n");

	fclose(fp);

}


/*
 * args: @players holds the player names.
 *
 * returns: nothing.
 *
 * Notes:
 * 		Will ask for the names of each player and 
 * 		store it in the 2D array for later use in 
 * 		the game.
 */
void getNames5(char players[SIX][MAX_NAME]) {

	int i;
	int len = 0;
	for(i = 0; i < SIX; i++) {
		printf("Enter player %d: ", i + 1);
		fgets(*(players + i), 14, stdin);
		len = strlen(players[i]);
		players[i][len-1] = '\0';
	}

	puts("");
}


/*
 * args: none. 
 *
 * returns: nothing.
 *
 * Notes: 
 *		Game loop. First we get the names of the players,
 *		then we open a file to start saving the game progress.
 *
 *		We then ask if we want to play a round. If no, the 
 *		game ends and we dislay the table with the total scores. 
 *		If yes, we will ask for the new scores for each player, 
 *		append them to the file, and finally we print the table.
 */
void gameWith5() {

	char answer[5];
	char players[SIX][MAX_NAME];
	char game[7][MAX_NAME] = { "3x3", "3x4", "4x4", "3x3x3",
															"3x3x4", "3x4x4", "4x4x4" };
	int totalScores[SIX] = { 0, 0, 0, 0, 0, 0 };
	int counter = 0;
	int done = 0;

	getNames5(players);
	writeFile(players);

	do {
		printf("Play a round? Enter yes or no: ");
		fgets(answer, 5, stdin);
		puts("");
		if(strcmp(answer, "no\n") == 0) {
			done = 1;	
			printDone();
			updateFile();
			printFile();
		}
		else {
			enterScores(players, totalScores, game);
			saveScores(players, totalScores, game);	
			printTable();
			puts("\n");
		}
		counter++;
	} while(done != 1);

}


/*
 * args: none.
 *
 * returns: nothing.
 *
 * Notes:
 * 		Main menu that calls the start of the game.
 */ 		
int main() {

	printf("┌---------------------------┐\n");
	printf("| Hello! This is telefunke! |\n");
	printf("└---------------------------┘\n");

	gameWith5();
	puts("\n");

	return 0;

}
