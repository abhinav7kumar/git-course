#include <iostream>
using namespace std;

void calculateResult(int marks) {
    if (marks < 0 || marks > 100) {
        cout << "Invalid marks entered." << endl;
        return;
    }

    if (marks >= 40) {
        cout << "Result: Pass\n";
        if (marks >= 75) cout << "Grade: A\n";
        else if (marks >= 60) cout << "Grade: B\n";
        else cout << "Grade: C\n";
    } else {
        cout << "Result: Fail\nGrade: F\n";
    }
}

int main() {
    int marks;
    cout << "Enter student marks: ";
    cin >> marks;
    calculateResult(marks);
    return 0;
}
