#include <iostream>
using namespace std;

int main() {
    int marks;
    cout << "Enter marks: ";
    cin >> marks;

    char grade;
    if (marks >= 75) grade = 'A';
    else if (marks >= 60) grade = 'B';
    else if (marks >= 40) grade = 'C';
    else grade = 'F';

    cout << "Result: " << (grade == 'F' ? "Fail" : "Pass") << endl;

    switch (grade) {
        case 'A': cout << "Grade: A\n"; break;
        case 'B': cout << "Grade: B\n"; break;
        case 'C': cout << "Grade: C\n"; break;
        default: cout << "Grade: F\n";
    }

    return 0;
}
