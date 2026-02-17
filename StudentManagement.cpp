#include <iostream>
#include <vector>
using namespace std;

struct Student {
    int roll;
    string name;
};

vector<Student> students;

void addStudent() {
    Student s;
    cin >> s.roll >> s.name;
    students.push_back(s);
}

void viewStudents() {
    for (auto s : students)
        cout << s.roll << " " << s.name << endl;
}

int main() {
    int choice;
    do {
        cout << "\n1.Add 2.View 3.Exit\n";
        cin >> choice;
        if (choice == 1) addStudent();
        else if (choice == 2) viewStudents();
    } while (choice != 3);
    return 0;
}
