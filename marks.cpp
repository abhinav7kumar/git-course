#include <iostream>
using namespace std;

void calculateResult(int marks) {
    if (marks >= 40)
        cout << "Pass";
    else
        cout << "Fail";
}

int main() {
    int students;
    cout << "Enter number of students: ";
    cin >> students;

    for (int i = 1; i <= students; i++) {
        int marks;
        cout << "\nEnter marks for student " << i << ": ";
        cin >> marks;
        calculateResult(marks);
    }
    return 0;
}
