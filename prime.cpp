#include <iostream>
using namespace std;

int main() {
    int a, b, c;

    cout << "Enter three numbers: ";
    cin >> a >> b >> c;

    // Find largest number
    int largest;
    if (a >= b && a >= c) {
        largest = a;
    } else if (b >= a && b >= c) {
        largest = b;
    } else {
        largest = c;
    }

    // Find smallest number
    int smallest;
    if (a <= b && a <= c) {
        smallest = a;
    } else if (b <= a && b <= c) {
        smallest = b;
    } else {
        smallest = c;
    }

    // Calculate sum and average
    int sum = a + b + c;
    double average = sum / 3.0;

    // Display results
    cout << "\n===== ANALYSIS =====" << endl;
    cout << "Numbers: " << a << ", " << b << ", " << c << endl;
    cout << "Largest number: " << largest << endl;
    cout << "Smallest number: " << smallest << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
