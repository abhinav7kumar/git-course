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