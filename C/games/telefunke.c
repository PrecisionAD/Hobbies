/*
 * Record keeping program. The way we keep track of scores and
 * print them to console is by opening a file (temp.txt)
 * and start saving the current points for the current round for each
 * player. 
 *
 * In the middle of the process the program will ask, after each round
 * has been played, to enter the scores for each player. This is done
 * dynamically (user selects to enter any players' score at will)
 * which saves times compared to entering the scores sequentially.
 *
 * There is also an option to amend any score at any time.
 *
 * At the end of the game or by user's choice, the file
 * scores.txt will be opened to append everything from temp.txt in an
 * attempt to save some time while printing the tables with scores.
 *
 * As of right now, up to 6 players can play.
 *
 * Author: Adrian Meneses
 * Date: 01/15/2021
 * v1.7
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIX 6
#define MAX_NAME 15 

// To compare who won at the end
struct player {
	char name[16];
	int score;
	int flag;
};

int row = 0;
int gameRound = 0;
int totalScore[SIX][5] = { {0}, {0}, {0}, {0}, {0}, {0} };



/*
 * args: 
 * 		None.
 *
 * returns: 
 * 		Nothing.
 *
 * Notes:
 * 		Let users know that there are no more games and
 * 		the final scores are being printed.
 */
void printDone() {
	
	printf("\n\n\n****************\n");
	printf("* FINAL SCORES *\n");
	printf("****************");

}


/*
 * args: @fileName contains the file to be opened
 * 			 @mode is how the file is to be read
 *
 * returns: a FILE pointer with the file requested.
 *
 * Notes:
 * 		This function was created to eliminate duplicate code 
 * 		throughout the program.
 */
FILE * openFile(char *fileName, char *mode) {

	FILE *fp = NULL;

	fp = fopen(fileName, mode);
	if(fp == NULL) {
		printf("The file requested could not be opened! (openFile function)\n");
		exit(1);
	}

	return fp;
}


/*
 * args:
 * 		None.
 *
 * returns: 
 * 		Nothing.
 *
 * Notes:
 * 		This will save the current scores (table) from the 
 * 		temp.txt file into the scores.txt file at the end 
 * 		of the game to prevent reading the complete scores.txt 
 * 		(where there is a history of all the games that have
 * 		been played) as it was originally.
 *
 * 		This is to save a little bit of time in opening and 
 * 		closing the file (temp.txt) each time during the game.
 */
void appendNewScores() {
	
	char buffer[100];
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;

	fp1 = openFile("scores.txt", "a");
	fp2 = openFile("temp.txt", "r");

	while(fgets(buffer, 100, fp2) != NULL) {
		fprintf(fp1, "%s", buffer);
	}

	fclose(fp1);
	fclose(fp2);

}


/*
 * args:
 * 		None.
 *
 * returns: 
 * 		Nothing.
 *
 * Notes:
 * 		Print everything that was saved (such as new scores)
 * 		to the file temp.txt for each player.
 */ 		
void printFile() {

	char buffer[100];
	FILE *fp = NULL;

	fp = openFile("temp.txt", "r");

	while(fgets(buffer, 100, fp) != NULL) {
		printf("%s", buffer);
	}

	fclose(fp);

}


/* args:
 * 		None.
 *
 * returns: 
 * 		Nothing.
 *
 * Notes:
 * 		This will add to the end of the table the total 
 * 		scores print out for each player.
 */ 		
void updateFile() {

	int i;
	FILE *fp = NULL;

	fp = openFile("temp.txt", "a");

	for(i = 0; i < SIX; i++) {
		fprintf(fp, "| %-7d", totalScore[i][0]);
	}

	fprintf(fp, "%s", "|Total Scores");
	fprintf(fp, "%s", "\n└--------┴--------┴--------┴--------┴--------┴--------┘\n");

	fclose(fp);

}


/*
 * args: 
 * 		None.
 *
 * returns:
 * 		Nothing.
 *
 * Notes:
 * 		Prints the table for the current game and adds the 
 * 		current total score for each player at the end.
 */
void printTable() {

	char buffer[100];
	FILE *fp = NULL;
	int i;

	fp = openFile("temp.txt", "r");

	/* Print the table from the file */
	while(fgets(buffer, 100, fp) != NULL) {
		printf("%s", buffer);
	}
	
	/* Add the total scores at the bottom of the table */
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
 * returns:
 * 		Nothing.
 *
 * Notes:
 * 		This will save to the file the header of the table 
 * 		with the names of each player. This function is
 * 		only run once everytime the program is run.
 */
void writeFile(char players[][MAX_NAME]) {

	int i;
	FILE *fp = NULL;

	fp = openFile("temp.txt", "a");

	fprintf(fp, "%s", "\n\n┌--------┐\n");
	fprintf(fp, "%s", "| TABLE  | \n");
	fprintf(fp, "%s", "├--------┼--------┬--------┬--------┬--------┬--------┐\n");

	/* Save players names to the file. */
	for(i = 0; i < SIX; i++) {
		fprintf(fp, "%c %-7s", '|', players[i]);
	}
	
	fprintf(fp, "%s", "|");
	fprintf(fp, "%s", "\n├--------┼--------┼--------┼--------┼--------┼--------┤\n");

	fclose(fp);

}


/*
 * args: 
 * 		None.
 *
 * returns:
 * 		Nothing.
 *
 * Notes:
 * 		Simply saves the dividers for each cell in the table 
 * 		to the file.
 */
void printDividers() {

	FILE *fp = NULL;

	fp = openFile("temp.txt", "a");

	fprintf(fp, "%s", "\n├--------┼--------┼--------┼--------┼--------┼--------┤\n");

	fclose(fp);

}


/*
 * args: @players contains the names of the player.
 * 			 @totalScores contains the scores for the players
 *
 * returns:
 * 		Nothing.
 *
 * Notes:
 * 		Print the difference in points from each player
 * 		with respect to whoever is currently leading the 
 * 		scoreboard (least amount of points). As an extra 
 * 		token, it will print a star for the leading
 * 		player or a skull for the bottom player.
 */
void scoreDiff(char players[][MAX_NAME], struct player *p) {

	int i, j;
	int temp = 0;
	int lowest = 0;
	int index = -1;
	int tempScore[SIX][5] = { {0}, {0}, {0}, {0}, {0}, {0} };

	// Copy the scores to display them later in order
	for(i = 0; i < SIX; i++) {
		tempScore[i][0] = totalScore[i][0];
	}
	
	// Sort the scores and reset the player flag to avoid printing double
	for(i = 0; i < SIX; i++) {
		lowest = tempScore[i][0];
		p[i].flag = 0;
		for(j = (i); j < SIX; j++) {
			if(tempScore[j][0] <= lowest) {
				lowest = tempScore[j][0];
				index = j;
			}
		}

		// Swap the lowest score and place it in new index
		temp = tempScore[i][0];
		tempScore[i][0] = lowest;
		tempScore[index][0] = temp;

	}

	printf("Points difference:\n");
	
	/* Print the difference in points */
	for(i = 0; i < SIX; i++) {
		for(j = 0; j < SIX; j++) {
			if(p[j].score == tempScore[i][0] && p[j].flag == 0) {
				printf("%d) %-7s +%d", (i + 1), p[j].name, tempScore[i][0] - tempScore[0][0]);
				if(i == 0) { printf(" ⭐"); }  // For winning player
				if(i == 5) { printf(" ☠ "); } // For lowest score
				p[j].flag = 1;

				// "Marks" a player as printed already
				if(i > 0) {
					tempScore[i][0] = -1;
				}
				puts("");
			}
		}
	}

}


/*
 * args: @players contains the names of the player.
 * 			 @totalScores contains the scores for the players
 * 			 @game contains the round type currently in play.
 *
 * returns: 
 * 		Nothing.
 *
 * Notes:
 * 		Prints the names of the players with a checkmark
 * 		if his/her score has been updated. Otherwise, it
 * 		prints his/her name without the checkmark to signal
 * 		that the player needs to be updated. The use of
 * 		if-else was elected because this function is
 * 		called from within a loop and because there are
 * 		6 players in total only. If a loop is used to print 
 * 		the names, the magnitude will be O(N^2).
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
		
	if(selected[5] != 1) { printf("6) %s", players[5]); }
	else { printf("6) %s ✓", players[5]); }

	puts("");
}


/*
 * args: @buffer contains the buffer to store the input.
 *
 * returns: the option number entered by user.
 *
 * Notes:
 * 		Created to simplify and eliminate duplicate code.
 */
int askInput(char *buffer) {

	int option = 0;
	
	printf("\nEnter option: ");
	fgets(buffer, 5, stdin);
	option = atoi(buffer);

	return option;

}



/*
 * args: @players contains the names of the players.
 * 			 @totalScores contains the scores for the players.
 * 			 @game contains the round type currently in play.
 *
 * returns:
 * 		Nothing.
 *
 * Notes:
 * 		This will ask to enter the points obtained for each
 * 		player after one round. If a mistake was made while
 * 		entering a score, the option to redo it on the spot
 * 		is available. All this is done dynamically instead 
 * 		of entering each score sequentially. 
 *
 * 		The selected[] array is used as a reference to mark 
 * 		each player as updated (the index contains a 0 if 
 * 		the player has not been updated and a 1 if player
 * 		was updated).
 */
void enterScores(char players[][MAX_NAME], int *totalScores, char game[][MAX_NAME], struct player *p) {

	int done = 0;
	int allDone = 0;
	int points = 0;
	int index = 0;
	int selected[6] = { 0, 0, 0, 0, 0, 0 };
	char option[6];
	char buffer[5];

	printf("╔═════════╗\n");
	printf("║ %-6s  ║ <=== Game you are currently playing!\n", game[gameRound++]);
	printf("╚═════════╝\n");
	
	while(done != 1) {
		printf("\nUpdate score for which player?\n");

		// If name has not been updated, print it without the checkmark
		printPlayers(selected, players);

		// Ask for player name to be updated
		index = askInput(option);

		if(index > 0 && index < 7) {
			// Check if player was updated already
			if(selected[index - 1] == 0) {
				printf("Enter new score for %s: ", players[index - 1]);
				fgets(option, 6, stdin);
				points = atoi(option);
			
				p[index - 1].score += points;     // Update player struct score
				totalScores[index - 1] += points; // Update points for the player
				selected[index - 1] = 1; 					// Mark player as updated
				allDone++;												// Update master count for loop

				// Let's confirm if points entered are correct
				printf("Is the score correct? ");
				fgets(buffer, 5, stdin);
				if(strcmp(buffer, "no\n") == 0 || strcmp(buffer, "n\n") == 0) {
					p[index - 1].score -= points;      // Reset player struct score
					totalScores[index - 1] -= points;  // Reset points
					selected[index - 1] = 0;					 // Unmark player
					allDone--;                         // Reset master count
					puts("");
				}
			}
			else {
				printf("That players has already been updated!\n");
			}
		}
		else {
			printf("Invalid option! Try again!\n");
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
 * returns:
 * 		Nothing.
 *
 * Notes:
 * 		This will save the points obtained by each player in a 
 * 		new row in the table (saved to the file). Saves a new
 * 		row divider.
 */
void saveScores(char players[][MAX_NAME], int *currentScore, char game[][MAX_NAME]) {

	int i;
	FILE *fp = NULL;

	fp = openFile("temp.txt", "a");

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
 * returns:
 * 		Nothing.
 *
 * Notes:
 * 		Will ask for the names of each player and 
 * 		store it in the 2D array for later use in 
 * 		the game. We also allocate space for the 
 * 		player struct and save the names of each
 * 		player.
 */
void getNames(char players[SIX][MAX_NAME], struct player * p) {

	int i;
	int len = 0;

	// Get names and initialize the player struct at the same time
	for(i = 0; i < SIX; i++) {
		p[i].score = 0;
		p[i].flag = 0;
		printf("Enter player %d: ", i + 1);
		fgets(*(players + i), 14, stdin);
		len = strlen(players[i]);
		players[i][len-1] = '\0';	// Gets rid of the '\n' at the end of each name
		strcpy(p[i].name, *(players + i));
	}

	puts("");
}


/*
 * args: @players contains the names of the players.
 *
 * returns: 
 * 		Nothing.
 *
 * Notes:
 * 		Let the players adjust their scores if a mistake was
 * 		made after each round. This can be done at any time.
 */
void adjustScore(char players[][MAX_NAME]) {
	
	int i;
	int done = 0;
	int option = 0;
	int newScore = 0;
	char buffer[10];

	// Print all players
	printf("\nAdjust score for which player?\n");
	for(i = 0; i < SIX; i++) {
		printf("%d) %-6s %-3d pts\n", (i + 1), players[i], totalScore[i][0]);
	}

	do {
		// Get the user's choice and make sure it's valid
		option = askInput(buffer);

		if(option < 1 || option > 6) { printf("Invalid option! Try again!\n"); }
		else { done = 1; }

	} while(done != 1);

	i = option; // To have a more readable array

	// Adjust the score
	printf("\nThe current score for %s is %d pts\n", players[i - 1], totalScore[i - 1][0]);
	printf("Enter the new score: ");
	fgets(buffer, 9, stdin);
	newScore = atoi(buffer);
	totalScore[i - 1][0] = newScore;
	printf("\nNew score of %d pts for player %s was updated.\n\n", totalScore[i - 1][0], players[i - 1]);
	sleep(2);

}


/*
 * args:
 * 		None.
 *
 * returns: the menu option selected by the user.
 *
 * Notes:
 * 		Show a menu for the game where users can select
 * 		as of right now three options which are to modify
 * 		the scores of a player, play a round, or end
 * 		the game.
 */
int option() {

	int option = 0;
	int done = 0;
	char buffer[5];

	printf("What would you like to do?\n");
	printf("1) Play a round\n");
	printf("2) Adjust a score\n");
	printf("3) End the game\n");

	do {
		// Ask for menu choice 
		option = askInput(buffer);

		// Check if input is valid 
		if(option < 1 || option > 3) {
			printf("\nThat's an invalid option! Try again!\n");
		}
		else {
			done = 1;
		}
	
	} while(done != 1);

	return option;

}



/*
 * args: none. 
 *
 * returns:
 * 		Nothing.
 *
 * Notes: 
 *		Game loop. First we get the names of the players,
 *		then we open a file to start saving the game progress as
 *		it develops (save it to the temp.txt file after each 
 *		round).
 *
 *		We then ask if we want to play a round. If not, the 
 *		game ends and we display the table with the total scores. 
 *		If yes, we will ask for the new scores for each player, 
 *		append them to the file (temp.txt), and then we print the
 *		table with the current scores.
 *
 * 		When the game ends, everything that was saved to the temp.txt
 * 		file will be copied to the scores.txt, the final scores
 * 		will be printed one last time and the temp.txt file will
 * 		be deleted from the directory as part of the clean up.
 *		append them to the file, and finally we print the current
 *		table with all the scores.
 *		
 *		In the end, the players will be able to see who won and
 *		the point difference.
 */
void gameStart() {

	struct player p[SIX];
	char players[SIX][MAX_NAME];
	char game[7][MAX_NAME] = { "3x3", "3x4", "4x4", "3x3x3",
															"3x3x4", "3x4x4", "4x4x4" };
	int totalScores[SIX] = { 0, 0, 0, 0, 0, 0 };
	int round = 0;
	int done = 0;
	int menuOption = 0;

	getNames(players, p);
	writeFile(players);

	do {
		// Ask for a menu option
		if(round < 7) { menuOption = option(); }
		else { menuOption = 3; }

		switch(menuOption) {
			case 1:
				enterScores(players, totalScores, game, p);
				saveScores(players, totalScores, game);	
				printTable();
				scoreDiff(players, p);
				puts("\n");
				break;

			case 2:
				adjustScore(players);
				break;

			case 3:
				printDone();
				updateFile();
				printFile();
				appendNewScores();
				scoreDiff(players, p);
				remove("temp.txt");
				done = 1;	
				break;

		}

		// One round was played
		round++;

	} while(done != 1);

}


/*
 * args: 
 * 		None.
 *
 * returns:
 * 		Nothing.
 *
 * Notes:
 * 		Main menu that calls the start of the game.
 */ 		
int main() {

	printf("┌---------------------------┐\n");
	printf("| Are you ready? Telefunke! |\n");
	printf("└---------------------------┘\n\n");

	gameStart();
	puts("\n");

	return 0;

}
