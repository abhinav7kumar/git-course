#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
};

void menu() {
    printf("\n===== LIBRARY SYSTEM =====\n");
    printf("1. Add Book\n");
    printf("2. View Books\n");
    printf("3. Exit\n");
    printf("Enter choice: ");
}

int main() {
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);

        if (choice == 3) break;
    }
    return 0;
}