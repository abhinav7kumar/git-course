#include <stdio.h>

struct Book {
    int id;
    char title[50];
};

struct Book books[5];
int count = 0;

void addBook() {
    scanf("%d %s", &books[count].id, books[count].title);
    count++;
}

void viewBooks() {
    int i;
    for(i = 0; i < count; i++)
        printf("%d - %s\n", books[i].id, books[i].title);
}

void deleteBook(int id) {
    int i, j;
    for(i = 0; i < count; i++) {
        if(books[i].id == id) {
            for(j = i; j < count-1; j++)
                books[j] = books[j+1];
            count--;
            return;
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
    printf("Not Found\n");
}

int main() {
    int choice, id;

    do {
        printf("\n1.Add 2.View 3.Delete 4.Search 5.Exit\n");
        scanf("%d", &choice);

        if(choice == 1) addBook();
        else if(choice == 2) viewBooks();
        else if(choice == 3) {
            scanf("%d", &id);
            deleteBook(id);
        }
        else if(choice == 4) {
            scanf("%d", &id);
            searchBook(id);
        }

    } while(choice != 5);

    return 0;
}