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
void addBook() {
    FILE *fp = fopen("books.txt", "a");
    struct Book b;

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Title: ");
    scanf(" %[^\n]", b.title);
    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);
    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fprintf(fp, "%d|%s|%s|%d\n", b.id, b.title, b.author, b.quantity);
    fclose(fp);

    printf("Book added successfully!\n");
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