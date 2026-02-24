#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showWelcome() {
    printf("===== Snake and Ladder Game =====\n");
    printf("Two Player Game\n");
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