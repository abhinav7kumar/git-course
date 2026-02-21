#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

void menu() {
    printf("\n===== Student Record System =====\n");
    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Exit\n");
    printf("Enter choice: ");
}

int main() {
    int choice;

    while (1) {
        menu();
        scanf("%d", &choice);

        if (choice == 3) {
            printf("Exiting...\n");
            break;
        }
    }

    return 0;
}