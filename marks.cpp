#include <iostream>
using namespace std;

void calculateResult(int marks) {
    if (marks >= 40) {
        cout << "Result: Pass" << endl;

        if (marks >= 75)
            cout << "Grade: A" << endl;
        else if (marks >= 60)
            cout << "Grade: B" << endl;
        else
            cout << "Grade: C" << endl;
    } else {
        cout << "Result: Fail" << endl;
        cout << "Grade: F" << endl;
    }
}

int main() {
    int marks;
    cout << "Enter student marks: ";
    cin >> marks;

    calculateResult(marks);
    return 0;
}
