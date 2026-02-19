#include <stdio.h>

int main() {
    int choice;

    do {
        printf("\n1.Add 2.View 3.Exit\n");
        scanf("%d", &choice);
    } while(choice != 3);

    return 0;
}