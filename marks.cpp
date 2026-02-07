#include <iostream>
using namespace std;

int main() {
    int marks;
    cout << "Enter student marks: ";
    cin >> marks;

    if (marks >= 40) {
        cout << "Result: Pass" << endl;
    } else {
        cout << "Result: Fail" << endl;
    }

    return 0;
}
