#include <iostream>
using namespace std;

struct Student {
    int roll;
    string name;
};

int main() {
    Student s;
    cout << "Enter Roll: ";
    cin >> s.roll;
    cout << "Enter Name: ";
    cin >> s.name;
    return 0;
}