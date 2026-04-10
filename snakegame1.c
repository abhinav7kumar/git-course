#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // for Sleep

#define MAX_PLAYERS 4
#define BOARD_SIZE 100
#define NUM_POWERUPS 5

typedef struct {
    int position;
    int type; // 0: extra turn, 1: skip opponent, 2: immunity
    int active;
} PowerUp;

void showWelcome() {
    printf("===== Snake and Ladder Game with Power-ups =====\n");
}

void showRules() {
    printf("\nRules:\n");
    printf("- Roll dice to move 1-6 spaces\n");
    printf("- Land on ladders to climb up, snakes to slide down\n");
    printf("- Traps skip your next turn\n");
    printf("- Land on power-ups [P] for bonuses: extra turn, skip opponent, immunity, or teleport\n");
    printf("- Active power-up locations and types are shown each turn\n");
    printf("- Last rolls are displayed for every player\n");
    printf("- The next player is previewed after each move\n");
    printf("- Player progress percentage is shown on the board\n");
    printf("- A leaderboard shows current player rankings each turn\n");
    printf("- Land on another player to bump them back to start\n");
    printf("- First to reach 100 wins!\n");
    printf("- Roll 6 for extra turn\n");
    printf("- Overshoot 100 bounces back\n");
    printf("- Press Enter before each dice roll\n\n");
}

const char* getPowerUpName(int type) {
    switch (type) {
        case 0: return "Extra Turn";
        case 1: return "Skip Opponent";
        case 2: return "Immunity";
        case 3: return "Teleport";
        default: return "Unknown";
    }
}

void displayPowerUpSummary(PowerUp powerUps[]) {
    int counts[4] = {0};
    for (int i = 0; i < NUM_POWERUPS; i++) {
        if (powerUps[i].active && powerUps[i].type >= 0 && powerUps[i].type < 4) {
            counts[powerUps[i].type]++;
        }
    }
    printf("Power-up summary: Extra Turn=%d, Skip Opponent=%d, Immunity=%d, Teleport=%d\n",
           counts[0], counts[1], counts[2], counts[3]);
}

void initializePowerUps(PowerUp powerUps[]) {
    for (int i = 0; i < NUM_POWERUPS; i++) {
        powerUps[i].position = (rand() % 99) + 1; // 1-99
        powerUps[i].type = rand() % 4; // 0,1,2,3
        powerUps[i].active = 1;
    }
}

void displayPlayerStatus(int immunity[], int skipTurn[], char names[][50], int numPlayers, PowerUp powerUps[], int powerUpsCollected[], int trapsHit[], int turns) {
    printf("\nPlayer Status (Turn %d):\n", turns + 1);
    int activePowerUps = 0;
    for (int pu = 0; pu < NUM_POWERUPS; pu++) {
        if (powerUps[pu].active) activePowerUps++;
    }
    printf("Active Power-ups remaining: %d\n", activePowerUps);
    if (activePowerUps > 0) {
        displayPowerUpSummary(powerUps);
        printf("Power-up details:\n");
        for (int pu = 0; pu < NUM_POWERUPS; pu++) {
            if (powerUps[pu].active) {
                printf("  - %s at %d\n", getPowerUpName(powerUps[pu].type), powerUps[pu].position);
            }
        }
    } else {
        printf("Power-up details: None\n");
    }
    printf("Power-ups collected so far:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("  %s: %d\n", names[i], powerUpsCollected[i]);
    }
    printf("Trap squares landed on:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("  %s: %d\n", names[i], trapsHit[i]);
    }
    for (int i = 0; i < numPlayers; i++) {
        printf("%s: ", names[i]);
        if (immunity[i]) printf("Immune ");
        if (skipTurn[i]) printf("Skipping next turn ");
        if (!immunity[i] && !skipTurn[i]) printf("Normal");
        printf("\n");
    }
    printf("\n");
}

void displayBoard(int positions[], char names[][50], int numPlayers) {
    printf("\nCurrent Board:\n");
    for (int i = 0; i < numPlayers; i++) {
        int progress = (positions[i] * 100) / 100;
        printf("%s: %d (spaces left: %d, progress: %d%%)\n", names[i], positions[i], 100 - positions[i], progress);
    }
    printf("Goal: 100\n\n");
}

void waitForPlayerRoll(const char *playerName) {
    printf("%s, press Enter to roll the dice...", playerName);
    fflush(stdin);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        ;
    }
}

void displayLeaderboard(int positions[], char names[][50], int numPlayers) {
    int order[MAX_PLAYERS];
    for (int i = 0; i < numPlayers; i++) {
        order[i] = i;
    }
    for (int i = 0; i < numPlayers - 1; i++) {
        for (int j = 0; j < numPlayers - 1 - i; j++) {
            if (positions[order[j]] < positions[order[j + 1]]) {
                int tmp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = tmp;
            }
        }
    }
    printf("Leaderboard:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("  %d. %s (%d)\n", i + 1, names[order[i]], positions[order[i]]);
    }
    printf("\n");
}

void displayLastRolls(int lastRolls[], char names[][50], int numPlayers) {
    printf("Last Rolls:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("  %s: %d\n", names[i], lastRolls[i]);
    }
    printf("\n");
}

void displayNextPlayer(int currentPlayer, char names[][50], int numPlayers, int extraTurn) {
    int nextPlayer = extraTurn ? currentPlayer : (currentPlayer + 1) % numPlayers;
    if (extraTurn) {
        printf("Next turn: %s (extra turn)\n\n", names[nextPlayer]);
    } else {
        printf("Next turn: %s\n\n", names[nextPlayer]);
    }
}

void displayVisualBoard(int positions[], int numPlayers, PowerUp powerUps[]) {
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
            int hasPowerUp = 0;
            int isLadder = 0;
            int isSnake = 0;
            int isTrap = 0;
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
            for (int pu = 0; pu < NUM_POWERUPS; pu++) {
                if (powerUps[pu].active && powerUps[pu].position == pos) {
                    hasPowerUp = 1;
                    break;
                }
            }
            // Check for ladders
            if (pos == 4 || pos == 9 || pos == 21 || pos == 63) {
                isLadder = 1;
            }
            // Check for snakes
            if (pos == 17 || pos == 28 || pos == 54 || pos == 87 || pos == 95 || pos == 99) {
                isSnake = 1;
            }
            // Check for traps
            if (pos == 23 || pos == 46 || pos == 72) {
                isTrap = 1;
            }
            if (playerOnSquare == 0) {
                printf("[M] ");
            } else if (playerOnSquare > 0) {
                printf("[%d] ", playerOnSquare);
            } else if (hasPowerUp) {
                printf("[P] ");
            } else if (isTrap) {
                printf("[T] ");
            } else if (isSnake) {
                printf("[S] ");
            } else if (isLadder) {
                printf("[L] ");
            } else {
                printf("[%2d] ", pos);
            }
        }
        printf("\n");
    }
    printf("\nLegend: [P] Power-up, [T] Trap, [S] Snake, [L] Ladder, [1-4] Players, [M] Multiple players\n\n");
}

int rollDice() {
    int dice = (rand() % 6) + 1;
    printf("\a"); // beep for dice roll
    return dice;
}

int checkSnakesAndLadders(int position) {
    if (position == 4) { printf("\aLadder! 4 -> 14\n"); return 14; }
    if (position == 9) { printf("\aLadder! 9 -> 31\n"); return 31; }
    if (position == 17) { printf("\aSnake! 17 -> 7\n"); return 7; }
    if (position == 21) { printf("\aLadder! 21 -> 42\n"); return 42; }
    if (position == 28) { printf("\aSnake! 28 -> 12\n"); return 12; }
    if (position == 54) { printf("\aSnake! 54 -> 34\n"); return 34; }
    if (position == 63) { printf("\aLadder! 63 -> 81\n"); return 81; }
    if (position == 87) { printf("\aSnake! 87 -> 36\n"); return 36; }
    if (position == 95) { printf("\aSnake! 95 -> 73\n"); return 73; }
    if (position == 99) { printf("\aSnake! 99 -> 5\n"); return 5; }
    return position;
}

int checkSpecialSquare(int position) {
    if (position == 23) { printf("\aTrap! 23 causes you to skip the next turn.\n"); return 1; }
    if (position == 46) { printf("\aTrap! 46 causes you to skip the next turn.\n"); return 1; }
    if (position == 72) { printf("\aTrap! 72 causes you to skip the next turn.\n"); return 1; }
    return 0;
}

int checkPowerUp(int *position, PowerUp powerUps[], int currentPlayer, int skipTurn[], int numPlayers, char names[][50], int *powerUpsCollected) {
    for (int pu = 0; pu < NUM_POWERUPS; pu++) {
        if (powerUps[pu].active && powerUps[pu].position == *position) {
            powerUps[pu].active = 0; // deactivate
            (*powerUpsCollected)++;
            printf("\a"); // beep for power-up
            if (powerUps[pu].type == 0) {
                printf("Power-up! %s gets an extra turn!\n", names[currentPlayer]);
                return 1; // extra turn
            } else if (powerUps[pu].type == 1) {
                int target = (currentPlayer + 1) % numPlayers;
                skipTurn[target] = 1;
                printf("Power-up! %s skips %s's next turn!\n", names[currentPlayer], names[target]);
            } else if (powerUps[pu].type == 2) {
                printf("Power-up! %s is now immune to traps!\n", names[currentPlayer]);
                return 2; // immunity
            } else if (powerUps[pu].type == 3) {
                int newPos = (rand() % 99) + 1;
                *position = newPos;
                printf("Power-up! %s teleports to position %d!\n", names[currentPlayer], newPos);
            }
            break;
        }
    }
    return 0;
}

int main() {
    srand(time(0));
    int numPlayers;
    char names[MAX_PLAYERS][50];
    int wins[MAX_PLAYERS] = {0};
    char playAgain;

    showWelcome();
    showRules();

    int choice;
    do {
        printf("1. New Game\n2. Load Game\nChoose: ");
        scanf("%d", &choice);
        if (choice == 1 || choice == 2) break;
        printf("Invalid choice.\n");
    } while (1);

    if (choice == 2) {
        FILE *file = fopen("savegame.txt", "r");
        if (file == NULL) {
            printf("No save file found. Starting new game.\n");
            choice = 1;
        } else {
            fscanf(file, "%d", &numPlayers);
            for (int i = 0; i < numPlayers; i++) {
                fscanf(file, "%s", names[i]);
                fscanf(file, "%d", &wins[i]);
            }
            fclose(file);
            printf("Loaded previous game data.\n");
        }
    }

    if (choice == 1) {
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
    }

    do {
        time_t startTime = time(NULL); // Record start time
        int positions[MAX_PLAYERS] = {0};
        int rolls[MAX_PLAYERS] = {0};
        int totalSpaces[MAX_PLAYERS] = {0}; // Track total spaces moved
        int lastRoll[MAX_PLAYERS] = {0};
        int skipTurn[MAX_PLAYERS] = {0};
        int immunity[MAX_PLAYERS] = {0};
        int powerUpsCollected[MAX_PLAYERS] = {0};
        int trapsHit[MAX_PLAYERS] = {0};
        PowerUp powerUps[NUM_POWERUPS];
        initializePowerUps(powerUps);
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

            waitForPlayerRoll(names[currentPlayer]);
            int dice = rollDice();
            rolls[currentPlayer]++;
            lastRoll[currentPlayer] = dice;
            totalSpaces[currentPlayer] += dice; // Track total spaces moved
            printf("\n%s rolled: %d\n", names[currentPlayer], dice);
            Sleep(500); // 0.5 second delay
            int newPosition = positions[currentPlayer] + dice;
            if (newPosition > 100) {
                int bounceBack = newPosition - 100;
                positions[currentPlayer] = 100 - bounceBack;
                printf("%s overshot 100 and bounces back to %d\n", names[currentPlayer], positions[currentPlayer]);
            } else {
                positions[currentPlayer] = newPosition;
            }
            positions[currentPlayer] = checkSnakesAndLadders(positions[currentPlayer]);
            int powerUpEffect = checkPowerUp(&positions[currentPlayer], powerUps, currentPlayer, skipTurn, numPlayers, names, &powerUpsCollected[currentPlayer]);
            int trapHit = checkSpecialSquare(positions[currentPlayer]);
            if (trapHit) {
                trapsHit[currentPlayer]++;
                if (immunity[currentPlayer]) {
                    printf("Immunity used! %s avoids the trap.\n", names[currentPlayer]);
                    immunity[currentPlayer] = 0;
                } else {
                    skipTurn[currentPlayer] = 1;
                }
            }
            if (powerUpEffect == 2) {
                immunity[currentPlayer] = 1;
            }

            for (int p = 0; p < numPlayers; p++) {
                if (p != currentPlayer && positions[p] == positions[currentPlayer] && positions[currentPlayer] != 0) {
                    positions[p] = 0;
                    printf("%s landed on %s and bumped them back to start!\n", names[currentPlayer], names[p]);
                }
            }

            printf("%s position: %d\n", names[currentPlayer], positions[currentPlayer]);
            displayBoard(positions, names, numPlayers);
            displayLastRolls(lastRoll, names, numPlayers);
            displayLeaderboard(positions, names, numPlayers);
            displayVisualBoard(positions, numPlayers, powerUps);
            displayPlayerStatus(immunity, skipTurn, names, numPlayers, powerUps, powerUpsCollected, trapsHit, turns);

            if (positions[currentPlayer] == 100) {
                winner = currentPlayer;
                break;
            }

            int extraTurn = (dice == 6) || (powerUpEffect == 1);
            if (extraTurn) {
                if (dice == 6) {
                    printf("%s rolled a 6 and gets an extra turn!\n", names[currentPlayer]);
                }
            } else {
                currentPlayer = (currentPlayer + 1) % numPlayers;
            }
            displayNextPlayer(currentPlayer, names, numPlayers, extraTurn);
            turns++;
        }

        printf("\n\a%s Wins!\n", names[winner]);
        wins[winner]++;
        time_t endTime = time(NULL); // Record end time
        double gameDuration = difftime(endTime, startTime); // Calculate duration in seconds
        printf("Game completed in %d turns and %.0f seconds.\n", turns, gameDuration);
        printf("Rolls taken by each player:\n");
        for (int i = 0; i < numPlayers; i++) {
            printf("%s: %d rolls\n", names[i], rolls[i]);
        }
        printf("Total spaces moved by each player:\n");
        for (int i = 0; i < numPlayers; i++) {
            printf("%s: %d spaces\n", names[i], totalSpaces[i]);
        }
        printf("Power-ups collected by each player:\n");
        for (int i = 0; i < numPlayers; i++) {
            printf("%s: %d\n", names[i], powerUpsCollected[i]);
        }
        printf("Trap squares landed on by each player:\n");
        for (int i = 0; i < numPlayers; i++) {
            printf("%s: %d\n", names[i], trapsHit[i]);
        }

        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\nFinal Scores:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%s: %d wins\n", names[i], wins[i]);
    }

    if (choice == 1) {
        FILE *file = fopen("savegame.txt", "w");
        if (file) {
            fprintf(file, "%d\n", numPlayers);
            for (int i = 0; i < numPlayers; i++) {
                fprintf(file, "%s\n%d\n", names[i], wins[i]);
            }
            fclose(file);
            printf("Game data saved.\n");
        }
    }

    return 0;
}
