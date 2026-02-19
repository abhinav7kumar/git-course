#include <stdio.h>

struct Book {
    int id;
    char title[50];
};

int main() {
    struct Book books[2];
    int i;

    for(i = 0; i < 2; i++) {
        printf("Enter ID: ");
        scanf("%d", &books[i].id);
        printf("Enter Title: ");
        scanf("%s", books[i].title);
    }

    return 0;
}