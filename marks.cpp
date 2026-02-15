#include <iostream>
using namespace std;

char calculateGrade(int marks) {
    if (marks >= 75) return 'A';
    if (marks >= 60) return 'B';
    if (marks >= 40) return 'C';
    return 'F';
}

int main() {
    int marks;
    cout << "Enter student marks: ";
    cin >> marks;

    char grade = calculateGrade(marks);
    cout << "Grade: " << grade << endl;
    cout << "Result: " << (grade != 'F' ? "Pass" : "Fail") << endl;

    return 0;
}
