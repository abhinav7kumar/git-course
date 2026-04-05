#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 4

void showWelcome() {
    printf("===== Snake and Ladder Game =====\n");
}

void displayBoard(int positions[], char names[][50], int numPlayers) {
    printf("\nCurrent Board:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%s: %d\n", names[i], positions[i]);
    }
    printf("Goal: 100\n\n");
}

void displayVisualBoard(int positions[], int numPlayers) {
    printf("\nVisual Board:\n");
    for (int row = 10; row >= 1; row--) {
        for (int col = 1; col <= 10; col++) {
            int pos;
            if (row % 2 == 0) {
                pos = (row - 1) * 10 + (11 - col);
            } else {
                pos = (row - 1) * 10 + col;
            }
            int playerOnSquare = -1;
            for (int p = 0; p < numPlayers; p++) {
                if (positions[p] == pos) {
                    if (playerOnSquare == -1) {
                        playerOnSquare = p + 1;
                    } else {
                        playerOnSquare = 0; // multiple
                        break;
                    }
                }
            }
            if (playerOnSquare == 0) {
                printf("[M] ");
            } else if (playerOnSquare > 0) {
                printf("[%d] ", playerOnSquare);
            } else {
                printf("[%2d] ", pos);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int rollDice() {
    return (rand() % 6) + 1;
}

int checkSnakesAndLadders(int position) {
    if (position == 4) { printf("Ladder! 4 -> 14\n"); return 14; }
    if (position == 9) { printf("Ladder! 9 -> 31\n"); return 31; }
    if (position == 17) { printf("Snake! 17 -> 7\n"); return 7; }
    if (position == 21) { printf("Ladder! 21 -> 42\n"); return 42; }
    if (position == 28) { printf("Snake! 28 -> 12\n"); return 12; }
    if (position == 54) { printf("Snake! 54 -> 34\n"); return 34; }
    if (position == 63) { printf("Ladder! 63 -> 81\n"); return 81; }
    if (position == 87) { printf("Snake! 87 -> 36\n"); return 36; }
    if (position == 95) { printf("Snake! 95 -> 73\n"); return 73; }
    if (position == 99) { printf("Snake! 99 -> 5\n"); return 5; }
    return position;
}

int checkSpecialSquare(int position) {
    if (position == 23) { printf("Trap! 23 causes you to skip the next turn.\n"); return 1; }
    if (position == 46) { printf("Trap! 46 causes you to skip the next turn.\n"); return 1; }
    if (position == 72) { printf("Trap! 72 causes you to skip the next turn.\n"); return 1; }
    return 0;
}

int main() {
    srand(time(0));
    int numPlayers;
    char names[MAX_PLAYERS][50];
    int wins[MAX_PLAYERS] = {0};
    char playAgain;

    showWelcome();

    do {
        printf("Enter number of players (2-4): ");
        scanf("%d", &numPlayers);
        if (numPlayers < 2 || numPlayers > 4) {
            printf("Invalid number. Must be 2-4.\n");
            continue;
        }
        break;
    } while (1);

    for (int i = 0; i < numPlayers; i++) {
        printf("Enter Player %d name: ", i + 1);
        scanf("%s", names[i]);
    }

    do {
        int positions[MAX_PLAYERS] = {0};
        int rolls[MAX_PLAYERS] = {0};
        int skipTurn[MAX_PLAYERS] = {0};
        int currentPlayer = 0;
        int turns = 0;
        int winner = -1;

        while (winner == -1) {
            if (skipTurn[currentPlayer]) {
                printf("\n%s misses this turn because of a trap.\n", names[currentPlayer]);
                skipTurn[currentPlayer] = 0;
                currentPlayer = (currentPlayer + 1) % numPlayers;
                turns++;
                continue;
            }

            int dice = rollDice();
            rolls[currentPlayer]++;
            printf("\n%s rolled: %d\n", names[currentPlayer], dice);
            int newPosition = positions[currentPlayer] + dice;
            if (newPosition > 100) {
                int bounceBack = newPosition - 100;
                positions[currentPlayer] = 100 - bounceBack;
                printf("%s overshot 100 and bounces back to %d\n", names[currentPlayer], positions[currentPlayer]);
            } else {
                positions[currentPlayer] = newPosition;
            }
            positions[currentPlayer] = checkSnakesAndLadders(positions[currentPlayer]);
            if (checkSpecialSquare(positions[currentPlayer])) {
                skipTurn[currentPlayer] = 1;
            }

            for (int p = 0; p < numPlayers; p++) {
                if (p != currentPlayer && positions[p] == positions[currentPlayer] && positions[currentPlayer] != 0) {
                    positions[p] = 0;
                    printf("%s landed on %s and bumped them back to start!\n", names[currentPlayer], names[p]);
                }
            }

            printf("%s position: %d\n", names[currentPlayer], positions[currentPlayer]);
            displayBoard(positions, names, numPlayers);
            displayVisualBoard(positions, numPlayers);

            if (positions[currentPlayer] == 100) {
                winner = currentPlayer;
                break;
            }

            if (dice == 6) {
                printf("%s rolled a 6 and gets an extra turn!\n", names[currentPlayer]);
            } else {
                currentPlayer = (currentPlayer + 1) % numPlayers;
            }
            turns++;
        }

        printf("\n%s Wins!\n", names[winner]);
        wins[winner]++;
        printf("Game completed in %d turns.\n", turns);
        printf("Rolls taken by each player:\n");
        for (int i = 0; i < numPlayers; i++) {
            printf("%s: %d rolls\n", names[i], rolls[i]);
        }

        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\nFinal Scores:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%s: %d wins\n", names[i], wins[i]);
    }

    return 0;
}
