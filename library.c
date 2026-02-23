#include <stdio.h>
#include <stdlib.h>

void showMenu() {
    printf("\n===== Library Management System =====\n");
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Add Book selected.\n");
                break;
            case 2:
                printf("Display Books selected.\n");
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}