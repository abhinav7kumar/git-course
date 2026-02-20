#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int width = 20, height = 20;
int gameOver;

void setup() {
    gameOver = 0;
}

void draw() {
    system("cls");

    for(int i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");

    for(int i = 0; i < height; i++) {
        printf("#");
        for(int j = 0; j < width; j++)
            printf(" ");
        printf("#\n");
    }

    for(int i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");
}

int main() {
    setup();
    while(!gameOver) {
        draw();
    }
    return 0;
}