#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
};
struct Member {
    int id;
    char name[100];
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
void viewBooks() {
    FILE *fp = fopen("books.txt", "r");
    struct Book b;

    printf("\n--- Book List ---\n");

    while (fscanf(fp, "%d|%[^|]|%[^|]|%d\n",
        &b.id, b.title, b.author, &b.quantity) != EOF) {

        printf("ID: %d | %s | %s | Qty: %d\n",
               b.id, b.title, b.author, b.quantity);
    }

    fclose(fp);
}
void searchBook() {
    FILE *fp = fopen("books.txt", "r");
    struct Book b;
    int searchId, found = 0;

    printf("Enter Book ID to search: ");
    scanf("%d", &searchId);

    while (fscanf(fp, "%d|%[^|]|%[^|]|%d\n",
        &b.id, b.title, b.author, &b.quantity) != EOF) {

        if (b.id == searchId) {
            printf("Found: %s by %s | Qty: %d\n",
                   b.title, b.author, b.quantity);
            found = 1;
        }
    }

    if (!found) printf("Book not found.\n");

    fclose(fp);
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