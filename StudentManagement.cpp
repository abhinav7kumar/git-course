#include <iostream>
using namespace std;

struct Student {
    int roll;
    string name;
};

int main() {
    Student s[2];
    for (int i = 0; i < 2; i++) {
        cout << "Enter Roll: ";
        cin >> s[i].roll;
        cout << "Enter Name: ";
        cin >> s[i].name;
    }
    return 0;
}#include <iostream>
using namespace std;

struct Student {
    int roll;
    string name;
};

int main() {
    Student s[2];
    for (int i = 0; i < 2; i++) {
        cout << "Enter Roll: ";
        cin >> s[i].roll;
        cout << "Enter Name: ";
        cin >> s[i].name;
    }
    return 0;
}