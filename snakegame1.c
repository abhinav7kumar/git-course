#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showWelcome() {
    printf("===== Snake and Ladder Game =====\n");
    printf("Two Player Game\n");
}
while (player1 < 100 && player2 < 100) {
    int dice = rollDice();
    printf("Player 1 rolled: %d\n", dice);
    player1 += dice;
    printf("Player 1 position: %d\n", player1);

    dice = rollDice();
    printf("Player 2 rolled: %d\n", dice);
    player2 += dice;
    printf("Player 2 position: %d\n", player2);
}
if (player1 + dice <= 100)
    player1 += dice;

int checkSnakesAndLadders(int position) {
    // Ladders
    if (position == 4) return 14;
    if (position == 9) return 31;
    if (position == 20) return 38;
    if (position == 28) return 84;

    // Snakes
    if (position == 17) return 7;
    if (position == 54) return 34;
    if (position == 62) return 19;
    if (position == 87) return 24;

    return position;
}
player1 = checkSnakesAndLadders(player1);
player2 = checkSnakesAndLadders(player2);

int rollDice() {
    return (rand() % 6) + 1;
}
int main() {
    srand(time(0));

    int player1 = 0;
    int player2 = 0;

    showWelcome();
    return 0;
}