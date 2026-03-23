#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showWelcome() {
    printf("===== Snake and Ladder Game =====\n");
}

void displayBoard(int p1, int p2) {
    printf("\nCurrent Board:\n");
    printf("Player 1: %d\n", p1);
    printf("Player 2: %d\n", p2);
    printf("Goal: 100\n\n");
}

int rollDice() {
    return (rand() % 6) + 1;
}

int checkSnakesAndLadders(int position) {
    if (position == 4) { printf("Ladder! 4 -> 14\n"); return 14; }
    if (position == 9) { printf("Ladder! 9 -> 31\n"); return 31; }
    if (position == 17) { printf("Snake! 17 -> 7\n"); return 7; }
    if (position == 54) { printf("Snake! 54 -> 34\n"); return 34; }
    return position;
}

int main() {
    srand(time(0));
    int player1 = 0, player2 = 0;
    int turn = 1;

    showWelcome();

    while (player1 < 100 && player2 < 100) {
        int dice = rollDice();

        if (turn == 1) {
            printf("\nPlayer 1 rolled: %d\n", dice);
            if (player1 + dice <= 100)
                player1 += dice;
            player1 = checkSnakesAndLadders(player1);
            printf("Player 1 position: %d\n", player1);
            displayBoard(player1, player2);
            turn = 2;
        } else {
            printf("\nPlayer 2 rolled: %d\n", dice);
            if (player2 + dice <= 100)
                player2 += dice;
            player2 = checkSnakesAndLadders(player2);
            printf("Player 2 position: %d\n", player2);
            displayBoard(player1, player2);
            turn = 1;
        }
    }

    if (player1 == 100)
        printf("\nPlayer 1 Wins!\n");
    else
        printf("\nPlayer 2 Wins!\n");

    return 0;
}