#include <iostream>
using namespace std;

void showResult(int marks) {
    cout << "Marks: " << marks << endl;

    if (marks >= 75)
        cout << "Result: Pass | Grade: A\n";
    else if (marks >= 60)
        cout << "Result: Pass | Grade: B\n";
    else if (marks >= 40)
        cout << "Result: Pass | Grade: C\n";
    else
        cout << "Result: Fail | Grade: F\n";
}

int main() {
    int marks;
    cout << "Enter student marks: ";
    cin >> marks;

    showResult(marks);
    return 0;
}
