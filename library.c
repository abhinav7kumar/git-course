#include <stdio.h>
#include <stdlib.h>

struct Book {
    int id;
    char title[50];
    char author[50];
    int issued;
};
void addBook() {
    struct Book b;

    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Title: ");
    scanf(" %[^\n]", b.title);

    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);

    b.issued = 0;

    books[bookCount++] = b;

    printf("Book added successfully!\n");
}
void displayBooks() {
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        printf("\nID: %d", books[i].id);
        printf("\nTitle: %s", books[i].title);
        printf("\nAuthor: %s", books[i].author);
        printf("\nStatus: %s\n", books[i].issued ? "Issued" : "Available");
    }
}
void showMenu() {
    printf("\n===== Library Management System =====\n");
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}


struct Book books[MAX];
int bookCount = 0;

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