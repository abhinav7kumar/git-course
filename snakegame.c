#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int width = 20, height = 20;
int gameOver;
int x, y;

void setup() {
    gameOver = 0;
    x = width / 2;
    y = height / 2;
}

void draw() {
    system("cls");

    for(int i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");

    for(int i = 0; i < height; i++) {
        printf("#");
        for(int j = 0; j < width; j++) {
            if(i == y && j == x)
                printf("O");
            else
                printf(" ");
        }
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