#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showWelcome() {
    printf("===== Snake and Ladder Game =====\n");
}

void displayBoard(int p1, int p2, char *n1, char *n2) {
    printf("\nCurrent Board:\n");
    printf("%s: %d\n", n1, p1);
    printf("%s: %d\n", n2, p2);
    printf("Goal: 100\n\n");
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

int main() {
    srand(time(0));
    char name1[50], name2[50];
    char playAgain;

    showWelcome();

    printf("Enter Player 1 name: ");
    scanf("%s", name1);
    printf("Enter Player 2 name: ");
    scanf("%s", name2);

    do {
        int player1 = 0, player2 = 0;
        int turn = 1;
        int turns = 0;

    while (player1 < 100 && player2 < 100) {
        int dice = rollDice();

        if (turn == 1) {
            printf("\n%s rolled: %d\n", name1, dice);
            if (player1 + dice <= 100)
                player1 += dice;
            player1 = checkSnakesAndLadders(player1);
            printf("%s position: %d\n", name1, player1);
            displayBoard(player1, player2, name1, name2);
            turn = 2;
        } else {
            printf("\n%s rolled: %d\n", name2, dice);
            if (player2 + dice <= 100)
                player2 += dice;
            player2 = checkSnakesAndLadders(player2);
            printf("%s position: %d\n", name2, player2);
            displayBoard(player1, player2, name1, name2);
            turn = 1;
        }
        turns++;
    }

    if (player1 == 100)
        printf("\n%s Wins!\n", name1);
    else
        printf("\n%s Wins!\n", name2);

    printf("Game completed in %d turns.\n", turns);

    printf("Play again? (y/n): ");
    scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}