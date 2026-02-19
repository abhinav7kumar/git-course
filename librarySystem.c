#include <stdio.h>

struct Book {
    int id;
    char title[50];
};

struct Book books[5];
int count = 0;

void addBook() {
    printf("Enter ID and Title: ");
    scanf("%d %s", &books[count].id, books[count].title);
    count++;
}

void viewBooks() {
    int i;
    for(i = 0; i < count; i++) {
        printf("%d - %s\n", books[i].id, books[i].title);
    }
}
void deleteBook(int id) {
    int i, j;
    for(i = 0; i < count; i++) {
        if(books[i].id == id) {
            for(j = i; j < count - 1; j++) {
                books[j] = books[j + 1];
            }
            count--;
            break;
        }
    }
}
void searchBook(int id) {
    int i;
    for(i = 0; i < count; i++) {
        if(books[i].id == id) {
            printf("Found: %s\n", books[i].title);
            return;
        }
    }
    printf("Book not found\n");
}
int main() {
    int choice;
    do {
        printf("\n1.Add 2.View 3.Exit\n");
        scanf("%d", &choice);

        if(choice == 1) addBook();
        else if(choice == 2) viewBooks();

    } while(choice != 3);

    return 0;
}