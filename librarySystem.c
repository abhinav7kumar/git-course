#include <stdio.h>

struct Book {
    int id;
    char title[50];
};

void addBook(struct Book *b) {
    scanf("%d %s", &b->id, b->title);
}

int main() {
    struct Book b;
    addBook(&b);
    return 0;
}