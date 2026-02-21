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
void searchStudent() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int searchId, found = 0;

    printf("Enter ID to search: ");
    scanf("%d", &searchId);

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF) {
        if (s.id == searchId) {
            printf("Found: %s | Marks: %.2f\n", s.name, s.marks);
            found = 1;
        }
    }

    if (!found)
        printf("Student not found.\n");

    fclose(fp);
}
void updateStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Student s;
    int updateId, found = 0;

    printf("Enter ID to update: ");
    scanf("%d", &updateId);

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF) {
        if (s.id == updateId) {
            printf("Enter new name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Record updated successfully.\n");
    else
        printf("Student not found.\n");
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