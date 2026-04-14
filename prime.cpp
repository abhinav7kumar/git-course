#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

bool isPerfectSquare(int n) {
    if (n < 0) return false;
    int root = sqrt(n);
    return root * root == n;
}

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
    int product = a * b * c;

    // Calculate range
    int range = largest - smallest;

    // Find middle value (median)
    int middle;
    if ((a >= b && a <= c) || (a >= c && a <= b)) {
        middle = a;
    } else if ((b >= a && b <= c) || (b >= c && b <= a)) {
        middle = b;
    } else {
        middle = c;
    }

    // Count even and odd numbers
    int evenCount = (a % 2 == 0) + (b % 2 == 0) + (c % 2 == 0);
    int oddCount = 3 - evenCount;

    // Check arrangement order
    bool isAscending = (a <= b && b <= c);
    bool isDescending = (a >= b && b >= c);

    // Check for duplicates
    bool hasDuplicates = (a == b) || (b == c) || (a == c);

    // Check number signs
    int negativeCount = (a < 0) + (b < 0) + (c < 0);
    int positiveCount = (a > 0) + (b > 0) + (c > 0);

    // Display results 
    cout << "\n===== ANALYSIS =====" << endl;
    cout << "Numbers: " << a << ", " << b << ", " << c << endl;
    cout << "Largest number: " << largest << endl;
    cout << "Smallest number: " << smallest << endl;
    cout << "Middle value: " << middle << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    cout << "Product: " << product << endl;
    cout << "Range: " << range << endl;
    cout << "Even numbers: " << evenCount << " | Odd numbers: " << oddCount << endl;
    cout << "Order: " << (isAscending ? "ASCENDING" : isDescending ? "DESCENDING" : "RANDOM") << endl;
    cout << "Duplicates: " << (hasDuplicates ? "YES" : "NO") << endl;
    cout << "Positive: " << positiveCount << " | Negative: " << negativeCount << endl;
    cout << "\n===== PRIME CHECK =====" << endl;
    cout << a << " is " << (isPrime(a) ? "PRIME" : "NOT PRIME") << endl;
    cout << b << " is " << (isPrime(b) ? "PRIME" : "NOT PRIME") << endl;
    cout << c << " is " << (isPrime(c) ? "PRIME" : "NOT PRIME") << endl;
    
    int primeCount = isPrime(a) + isPrime(b) + isPrime(c);
    cout << "\nTotal PRIME numbers: " << primeCount << " out of 3" << endl;
    
    cout << "\n===== PERFECT SQUARE CHECK =====" << endl;
    cout << a << " is " << (isPerfectSquare(a) ? "PERFECT SQUARE" : "NOT A PERFECT SQUARE") << endl;
    cout << b << " is " << (isPerfectSquare(b) ? "PERFECT SQUARE" : "NOT A PERFECT SQUARE") << endl;
    cout << c << " is " << (isPerfectSquare(c) ? "PERFECT SQUARE" : "NOT A PERFECT SQUARE") << endl;

    return 0;
}
