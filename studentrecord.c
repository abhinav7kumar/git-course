#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

void menu() {
    printf("\n===== Student Record System =====\n");
    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Exit\n");
    printf("Enter choice: ");
}
void addStudent() {
    FILE *fp = fopen("students.txt", "a");
    struct Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" [^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.id, s.name, s.marks);
    fclose(fp);

    printf("Student Added Successfully!\n");
}
void viewStudents() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;

    printf("\n--- Student List ---\n");

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF) {
        printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
}
int main() {
    int choice;

    while (1) {
        menu();
        scanf("%d", &choice);

        if (choice == 3) {
            printf("Exiting...\n");
            break;
        }
    }

    return 0;
}